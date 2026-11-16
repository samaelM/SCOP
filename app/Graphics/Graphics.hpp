#ifndef SCOP_GRAPHICS_HPP
#	define SCOP_GRAPHICS_HPP

#	include <iostream>										//Used to print info on the stdout
#	include <vector>										//Used to store data in better arrays
#	include <math.h>										//Used for angles calculation (radians, for matrices)
#	include <chrono>										//Used to calculate time

#	include "../../ressources/lib/glad/include/glad/gl.h"	//Used to find opengl functions and types
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

class Camera {
	private:
		GLfloat _target[3] = {0.0f, 0.0f, 0.0f};
		float _yaw = 0.0f;		// radians, rotation around the Y axis
		float _pitch = 0.0f;	// radians, rotation around the X axis
		float _radius = 3.0f;	// distance from the target

		float _orbitSensitivity = 0.005f;
		float _zoomSensitivity = 0.3f;
		float _minRadius = 0.5f;
		float _maxRadius = 20.0f;

	public:
		Camera() = default;
		~Camera() = default;

		void orbit(float deltaX, float deltaY);
		void zoom(float amount);
		void reset();

		void getPosition(GLfloat *out) const;
		void getViewMatrix(GLfloat *out) const;
};

class Mesh {
	private:
		GLuint _VAO = 0;
		GLuint _VBO = 0;
		GLuint _EBO = 0;

		std::vector<Vertex> _vertices;
		std::vector<GLuint> _faces;

		Deltas _deltas;

		GLuint _texturePercentUniform = 0;
		GLfloat _texturePercent = 0.0f;
		bool _showTexture = false;

		GLfloat _projection[16] = M_PROJECTION;
		GLuint _projectionUniform = 0;

		GLfloat _model[16] = M_MODEL;
		GLuint _modelUniform = 0;

		GLfloat _view[16] = M_VIEW;
		GLuint _viewUniform = 0;

		GLuint _DXUniform = 0;
		GLuint _DYUniform = 0;
		GLuint _DZUniform = 0;

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

		void setView(const GLfloat *v) { memcpy(_view, v, sizeof(_view)); }
		void setProjection(const GLfloat *p) { memcpy(_projection, p, sizeof(_projection)); }

		void changeTexture() {
			_showTexture = !_showTexture;
			std::cout << "Changing texture" << std::endl;
		}

		void move(const float direction, const Axis axis, const float &deltaTime);
		void rotate(const float direction, const Axis axis, const float &deltaTime);
		void show(const float deltaTime);
};

class Texture {
	private:
		GLuint _texture = 0;

	public:
		Texture(std::vector<unsigned char> &imageData, GLsizei height, GLsizei width);
		Texture();
		~Texture();

		void bind() const;
		GLuint getId() const { return _texture; };
};

#endif
