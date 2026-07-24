#ifndef SCOP_PARSER_HPP
#	define SCOP_PARSER_HPP

#	include <iostream>										//Used to print info on the stdout
#	include <fstream>										//Used to open files

#	include "../../ressources/lib/glad/include/glad/glad.h"	//Used to find opengl functions and types
#	include "../Graphics/Graphics.hpp"						//Used for the Mesh, Texture and Shader classes
#	include "Data.hpp"						//Used for the Mesh, Texture and Shader classes

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