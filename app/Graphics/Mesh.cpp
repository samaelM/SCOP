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

	// glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(GLfloat)));
	// glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	this->_VBO = VBO;
	return 1;
}

Mesh::~Mesh() {
}