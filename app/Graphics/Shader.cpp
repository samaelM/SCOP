#include "Graphics.hpp"
#include "../utils/utils.hpp"

Shader::Shader(const std::string &vertShPath, const std::string &fragShPath) {
	this->init();
	this->addVertexShader(vertShPath);
	this->addFragmentShader(fragShPath);
	this->link();
}

void Shader::init() {
	this->_shaderProgram = glCreateProgram();
}

void Shader::addVertexShader(const std::string &path) {
	const std::string content = load(path);
	const char *source = content.c_str();
	// std::cout << source << std::endl;
	const GLuint shader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(shader, 1, &source , NULL);
	glCompileShader(shader);
	glAttachShader(this->_shaderProgram, shader);

	glDeleteShader(shader);
}

void Shader::addFragmentShader(const std::string &path) {
	const std::string content = load(path);
	const char *source = content.c_str();
	// std::cout << source << std::endl;
	const GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(shader, 1, &source , NULL);
	glCompileShader(shader);
	glAttachShader(this->_shaderProgram, shader);

	glDeleteShader(shader);
}

void Shader::link() {
	glLinkProgram(this->_shaderProgram);
}

Shader::~Shader() {
	//delete shader program
}
