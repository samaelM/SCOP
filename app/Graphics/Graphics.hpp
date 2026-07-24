#ifndef SCOP_GRAPHICS_HPP
#	define SCOP_GRAPHICS_HPP

#	include <iostream>										//Used to print info on the stdout
#	include <vector>										//Used to store data in better arrays

#	include "../../ressources/lib/glad/include/glad/glad.h"	//Used to find opengl functions and types
#	include "../Parser/Parser.hpp"							//Used to parse .obj file
#	include "../Parser/Data.hpp"							//Used to parse .obj file

#	ifndef SCOP_VERTEX
#		define SCOP_VERTEX
struct Vertex {
	GLfloat position[3];
	GLfloat texCoords[2];
};
#	endif

class Mesh {
	private:
		GLuint _VAO = 0;
		GLuint _VBO = 0;
		std::vector<Vertex> _vertices;
		std::vector<GLuint> _faces;

		uint32_t init(const Data &data);

	public:
		Mesh(const std::string &path);
		Mesh();
		~Mesh();

		const GLuint &getVBO() const {return _VBO;};
		const GLuint &getVAO() const {return _VAO;};
		const GLsizei nbFaces() const {return _vertices.size();};
		const GLsizei nbVertices() const {return _faces.size();};
};

class Shader {
	private:
		GLuint _shaderProgram = 0;
		void init();
		void addVertexShader(const std::string &path);
		void addFragmentShader(const std::string &path);
		void link();

	public:
		Shader(const std::string &vertShPath, const std::string &fragShPath);
		Shader() = default;
		~Shader();

		GLuint getShader() const {return _shaderProgram;};
};

class Texture {
	private:
		unsigned char *_textureData;
		GLuint _texture = 0;

	public:
		Texture(const std::string &path);
		Texture();
		~Texture();
};

#endif