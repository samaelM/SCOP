#include "Graphics.hpp"

Texture::Texture(std::vector<unsigned char> &imageData, GLsizei height, GLsizei width) {
	glGenTextures(1, &this->_texture);
	glBindTexture(GL_TEXTURE_2D, this->_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (!imageData.empty()) {
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData.data());
		std::cout << "texture loaded!" << std::endl;
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture() {
	;
}

void Texture::bind() const {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->_texture);
}

Texture::~Texture() {
	glDeleteTextures(1, &this->_texture);
}
