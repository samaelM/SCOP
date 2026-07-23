#ifndef SCOP_GRAPHICS_HPP
#	define SCOP_GRAPHICS_HPP

#	include <iostream>										//Used to print info on the stdout
#	include <vector>										//Used to store data in better arrays

#	include "../../ressources/lib/glad/include/glad/glad.h"	//Used to find opengl functions and types
#	include "../Parser/Parser.hpp"							//Used to parse .obj file

struct Vertex {
	GLfloat position[3];
};

class Mesh {
	private:
		GLuint _VAO;
		GLuint _VBO;
		GLsizei _size;
		GLsizei _nbFaces;

		uint32_t addVBO(const Data data);

	public:
		Mesh();
		~Mesh();

		const GLuint &getVBO() const {return _VBO;};
		const GLuint &getVAO() const {return _VAO;};
		const GLsizei size() const {return _size;};
		const GLsizei nbFaces() const {return _nbFaces;};
};

class Shader {
	private:
		GLuint _shaderProgram = 0;
		void init();
		void addVertexShader(const GLchar *source);
		void addFragmentShader(const GLchar *source);
		void link();

	public:
		Shader();
		~Shader();

		GLuint getShader() const {return _shaderProgram;};
};

class Texture {
	private:
		unsigned char *_textureData;
		GLuint _texture = 0;

	public:
		Texture();
		~Texture();
};

#endif