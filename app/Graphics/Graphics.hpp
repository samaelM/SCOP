#ifndef SCOP_GRAPHICS_HPP
#	define SCOP_GRAPHICS_HPP

#	include <iostream>										//Used to print info on the stdout
#	include <vector>										//Used to store data in better arrays
#	include <math.h>										//Used for angles calculation (radians, for matrices)

#	include "../../ressources/lib/glad/include/glad/glad.h"	//Used to find opengl functions and types
#	include "../utils/utils.hpp"							//Used for matrix calculus

#	define M_PROJECTION {		\
		0.0f, 0.0f, 0.0f, 0.0f,	\
		0.0f, 0.0f, 0.0f, 0.0f,	\
		0.0f, 0.0f, 0.0f, 0.0f,	\
		0.0f, 0.0f, 0.0f, 1.0f	\
	}

#	define M_MODEL {			\
		1.0f, 0.0f, 0.0f, 0.0f,	\
		0.0f, 1.0f, 0.0f, 0.0f,	\
		0.0f, 0.0f, 1.0f, 0.0f,	\
		0.0f, 0.0f, 0.0f, 1.0f	\
	}

#	define M_VIEW {				\
		1.0f, 0.0f, 0.0f, 0.0f,	\
		0.0f, 1.0f, 0.0f, 0.0f,	\
		0.0f, 0.0f, 1.0f, 0.0f,	\
		0.0f, 0.0f, 0.0f, 1.0f	\
	}

struct Vertex {
	GLfloat position[3];
	GLfloat texCoords[2];
};

struct Deltas {
	GLfloat position[3] = {0.0f};
	GLfloat rotation[3] = {0.0f};
};

enum Direction {
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	FORWARD,
	BACKWARD,
};

enum Axis {
	X,
	Y,
	Z
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

		const GLuint &getShader() const {return _shaderProgram;};
};

class Mesh {
	private:
		GLuint _VAO = 0;
		GLuint _VBO = 0;
		
		std::vector<Vertex> _vertices;
		std::vector<GLuint> _faces;

		Deltas _deltas;

		GLfloat _projection[16] = M_PROJECTION;
		GLuint _projectionUniform;
		
		GLfloat _model[16] = M_MODEL;
		GLuint _modelUniform;
		
		GLfloat _view[16] = M_VIEW;
		GLuint _viewUniform;

		GLuint _DXUniform;
		GLuint _DYUniform;
		GLuint _DZUniform;

		uint32_t init();

		void rotateX(const float &deltaAngle);
		void rotateY(const float &deltaAngle);
		void rotateZ(const float &deltaAngle);

	public:
		Mesh(const std::vector<Vertex> vertices, const std::vector<GLuint> faces);
		Mesh() = default;
		~Mesh();

		const GLuint &getVBO() const {return _VBO;};
		const GLuint &getVAO() const {return _VAO;};
		GLsizei nbFaces() const {return _faces.size();};
		GLsizei nbVertices() const {return _vertices.size();};

		void prepare(const Shader &shader);

		void move(const float direction, const Axis axis, const float &deltaTime);
		void rotate(const float direction, const Axis axis, const float &deltaTime);
		void show();
};

class Texture {
	private:
		unsigned char *_textureData;
		GLuint _texture = 0;
		void init(const std::string &path);

	public:
		Texture(const std::string &path);
		Texture();
		~Texture();
};

#endif
