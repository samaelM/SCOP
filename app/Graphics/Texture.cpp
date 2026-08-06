#include "Graphics.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../../ressources/lib/stb_image.h"

Texture::Texture(std::vector<unsigned char> &imageData, GLsizei height, GLsizei width) {
	glGenTextures(1, &this->_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	this->_textureData = imageData.data();
	std::cout << std::to_string(imageData.size()) << " " << std::to_string(height * width *3) << std::endl;
	if (this->_textureData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->_textureData);
		std::cout << "texture loaded!" << std::to_string(errno) << std::endl;
	}
	else
	{//+THROW
	    std::cout << "Failed to load texture" << std::endl;
	} 
}

Texture::Texture() {
	;
}

Texture::~Texture() {
	free(this->_textureData);
}
