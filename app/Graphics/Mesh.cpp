#include "Graphics.hpp"

Mesh::Mesh(const std::vector<Vertex> vertices, const std::vector<GLuint> faces) :_vertices(vertices), _faces(faces) {
	this->init();
}

uint32_t Mesh::init() {
	GLuint VBO, EBO;
	
	const GLfloat *vert = (const GLfloat *)this->_vertices.data();
	
	const GLuint *fac = this->_faces.data();
	
	GLsizei size = this->_vertices.size() * sizeof(Vertex);

	glGenVertexArrays(1, &this->_VAO);
	glBindVertexArray(this->_VAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vert, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_faces.size() * sizeof(GLuint), fac, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	this->_VBO = VBO;
	return 1;
}

void Mesh::prepare(const Shader &shader) {
	this->_DXUniform = glGetUniformLocation(shader.getShader(), "dx");
	this->_DYUniform = glGetUniformLocation(shader.getShader(), "dy");
	this->_DZUniform = glGetUniformLocation(shader.getShader(), "dz");

	this->_modelUniform = glGetUniformLocation(shader.getShader(), "m_model");
	this->_projectionUniform = glGetUniformLocation(shader.getShader(), "m_projection");
	this->_viewUniform = glGetUniformLocation(shader.getShader(), "m_view");
}

void Mesh::rotateX(const float &deltaAngle) {
	const float c = std::cos(deltaAngle);
	const float s = std::sin(deltaAngle);
		
	const float deltaR[16] = {
		1.0f,	0.0f,	0.0f,	0.0f,
		0.0f,	c,		s,		0.0f,
		0.0f,	-s,		c,		0.0f,
		0.0f,	0.0f,	0.0f,	1.0f
	};

	multiplyMatrix(this->_model, deltaR, this->_model);
}

void Mesh::rotateY(const float &deltaAngle) {
	const float c = std::cos(deltaAngle);
	const float s = std::sin(deltaAngle);
		
	const float deltaR[16] = {
		c,		0.0f,	-s,		0.0f,
		0.0f,	1.0f,	0.0f,	0.0f,
		s,		0.0f,	c,		0.0f,
		0.0f,	0.0f,	0.0f,	1.0f
	};

	multiplyMatrix(this->_model, deltaR, this->_model);
}

void Mesh::rotateZ(const float &deltaAngle) {
	const float c = std::cos(deltaAngle);
	const float s = std::sin(deltaAngle);
		
	const float deltaR[16] = {
		 c,		s,		0.0f,	0.0f,
		-s,		c,		0.0f,	0.0f,
		 0.0f,	0.0f,	1.0f,	0.0f,
		 0.0f,	0.0f,	0.0f,	1.0f
	};

	multiplyMatrix(this->_model, deltaR, this->_model);
}

void Mesh::rotate(const float direction, const Axis axis, const float &deltaTime) {
	const float deltaAngle = direction * (static_cast<float>(M_PI) * deltaTime);

	switch (axis) {
		case Axis::X:
			this->rotateX(deltaAngle);
			break;
		case Axis::Y:
			this->rotateY(deltaAngle);
			break;
		case Axis::Z:
			this->rotateZ(deltaAngle);
			break;
		default:
			break;
	}
}

void Mesh::move(const float direction, const Axis axis, const float &deltaTime) {
	(void)deltaTime;
	switch (axis)
	{
	case Axis::X:
		this->_deltas.position[0] += direction * 0.01;
		break;
	case Axis::Y:
		this->_deltas.position[1] += direction * 0.01;
		break;
	case Axis::Z:
		this->_deltas.position[2] += direction * 0.01;
		break;
	
	default:
		break;
	}
}

void Mesh::show() {
	perspective(this->_projection, M_PI / 2, 800/800, 0.1f, 100.0f);
	GLfloat vec[3] = {0.0f, 0.0f, -3.0f};
	translate(this->_view, vec);

	glUniform1f(this->_DXUniform, this->_deltas.position[0]);
	glUniform1f(this->_DYUniform, this->_deltas.position[1]);
	glUniform1f(this->_DZUniform, this->_deltas.position[2]);

	glUniformMatrix4fv(this->_modelUniform, 1, GL_FALSE, this->_model);
	glUniformMatrix4fv(this->_viewUniform, 1, GL_FALSE, this->_view);
	glUniformMatrix4fv(this->_projectionUniform, 1, GL_FALSE, this->_projection);
}

Mesh::~Mesh() {
}
