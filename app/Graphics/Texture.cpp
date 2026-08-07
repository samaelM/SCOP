#include "Graphics.hpp"

Texture::Texture(std::vector<unsigned char> &imageData, GLsizei height, GLsizei width) {
	glGenTextures(1, &this->_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	this->_textureData = imageData.data();
	if (this->_textureData) {
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->_textureData);
		std::cout << "texture loaded!" << std::to_string(errno) << std::endl;
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	} 
}

Texture::Texture() {
	;
}

Texture::~Texture() {
}
