#ifndef SCOP_PARSER_HPP
#	define SCOP_PARSER_HPP

#	include <iostream>										//Used to print info on the stdout
#	include <fstream>										//Used to open files

#	include "../../ressources/lib/glad/include/glad/glad.h"	//Used to find opengl functions and types
#	include "../Graphics/Graphics.hpp"						//Used for the Mesh, Texture and Shader classes

class Data {
	private:
		std::vector<Vertex> _vertex;
		std::vector<GLuint> _faces;
		void normalizeVertices();

	public:
		Data() = default;
		~Data() = default;

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

class Parser
{
	private:
		static std::fstream openFile(std::string &fileName);
		static Data parseFile(std::fstream &file);

	public:
		static Data getData(std::string fileName);
		virtual void pure() = 0;
};

#endif