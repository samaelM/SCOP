#ifndef SCOP_PARSER_HPP
#	define SCOP_PARSER_HPP

#	include <iostream>										//Used to print info on the stdout
#	include <fstream>										//Used to open files
#	include <optional>										//Used to make return value optionnal

#	include "../../ressources/lib/glad/include/glad/glad.h"	//Used to find opengl functions and types
#	include "../Graphics/Graphics.hpp"						//Used for the Mesh, Texture and Shader classes

struct tga_header {
	const u_int8_t IDLen;
	const u_int8_t colorMapType;
	const u_int8_t imageType;

	const u_int16_t imgIndex;
	const u_int16_t colorMapLen;
	const u_int8_t colorMapEntrySize;

	const u_int16_t xOrigin;
	const u_int16_t yOrigin;
	const u_int16_t imgWidth;
	const u_int16_t imgHeight;
	const u_int8_t pixelDepth;
	const u_int8_t imgDescriptor;
};

class MeshData {
	private:
		std::vector<Vertex> _vertex;
		std::vector<GLuint> _faces;

	public:
		MeshData() = default;
		~MeshData() = default;

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
		void normalizeVertices();

		class NoVertex : public std::exception {
			virtual const char* what() const throw() {
				return "there is ony one vertex in memory";
			}
		};
};

class TextureData {
	private:
	public:
		std::vector<unsigned char> _pixels;
		GLsizei _height;
		GLsizei _width;
		TextureData(GLsizei height, GLsizei width) :_height(height), _width(width) {
			_pixels.reserve(height * width * 3);
			std::cout << std::to_string(height * width) << " | " << std::to_string(height * width * 3) << std::endl;
		};
		void fillPixels(const unsigned char *ptr) {
			size_t index = 0;
			size_t end = _height * _width * 3;

			while (index < end) {
				_pixels.push_back(*(ptr + index + 2));
				_pixels.push_back(*(ptr + index + 1));
				_pixels.push_back(*(ptr + index));
				index += 3;
			}
		}
		~TextureData() = default;
};

class Parser
{
	private:
		static std::fstream openFile(std::string &fileName);
		static MeshData parseMeshFile(std::fstream &file);

	public:
		static MeshData getMeshData(std::string fileName);
		static std::optional<TextureData> getTextureData(std::string fileName);
		virtual void pure() = 0;

		class IncorectData : public std::exception {
			private:
			std::string _msg;
			public:
			IncorectData(unsigned long linenb, std::string line){
				_msg = "file has incorrect data at line " + std::to_string(linenb) + ": " + line;
			}
			virtual const char* what() const throw() {
				return _msg.c_str();
			}
		};
		class UnsupportedFile : public std::exception {
			virtual const char* what() const throw() {
				return ("file is not supported");
			}
		};
};

#endif