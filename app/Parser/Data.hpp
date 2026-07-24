#ifndef SCOP_DATA_HPP
#	define SCOP_DATA_HPP
#	include <vector>										//Used to store data in better arrays
#	include "../../ressources/lib/glad/include/glad/glad.h"	//Used to find opengl functions and types

#	ifndef SCOP_VERTEX
#	define SCOP_VERTEX
struct Vertex {
	GLfloat position[3];
	GLfloat texCoords[2];
};
#	endif
class Data {
	private:
		std::vector<Vertex> _vertex;
		std::vector<GLuint> _faces;
		void normalizeVertices();

	public:
		Data();
		~Data();

		void addVertex(Vertex vec) { _vertex.push_back(vec);};
		void addFace3(GLuint face[3]) {
			_faces.push_back(face[0]);
			_faces.push_back(face[1]);
			_faces.push_back(face[2]);
		};
		void addFace4(GLuint face[4]) {
			_faces.push_back(face[0]);
			_faces.push_back(face[1]);
			_faces.push_back(face[2]);
			_faces.push_back(face[0]);
			_faces.push_back(face[2]);
			_faces.push_back(face[3]);
		};

		Vertex getVec(size_t index) const { return _vertex[index];};
		const std::vector<Vertex> &getVertices() const {return _vertex;};
		const std::vector<GLuint> &getFaces() const {return _faces;};

		class NoVertex : public std::exception {
			virtual const char* what() const throw() {
				return "there is ony one vertex in memory";
			}
		};
};
#endif