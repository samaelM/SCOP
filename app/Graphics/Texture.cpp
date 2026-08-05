#include "Graphics.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../../ressources/lib/stb_image.h"

Texture::Texture(std::vector<unsigned char> &imageData, GLsizei height, GLsizei width) {
	// int width, height, nrChannels;
	glGenTextures(1, &this->_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// this->_textureData = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	this->_textureData = imageData.data();
	std::cout << std::to_string(imageData.size()) << std::endl;
	if (this->_textureData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->_textureData);
		// std::cout << "after crash?" << std::endl;
		std::cout << "texture loaded!" << std::endl;
	}
	else
	{//+THROW
	    std::cout << "Failed to load texture" << std::endl;
	} 
	// stbi_image_free(this->_textureData);
}

Texture::Texture() {
	;
}

Texture::~Texture() {
	free(this->_textureData);
}