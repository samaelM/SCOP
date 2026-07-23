#ifndef SCOP_WINDOW_HPP
#	define SCOP_WINDOW_HPP

#	include <iostream>										//Used to print info on the stdout
#	include <exception>										//Used for throwing exceptions
#	include <math.h>										//Used for angles calculation (radians, for matrices)
#	include <chrono>										//Used to calculate delta time
#	include <GLFW/glfw3.h>									//Used to the window

#	include "../../ressources/lib/glad/include/glad/glad.h"	//Used to find opengl functions and types
#	include "../Graphics/Graphics.hpp"						//Used for the Mesh, Texture and Shader classes
#	include "../Parser/Parser.hpp"							//Used to parse .obj file


//A basic vertex shader in case the user don't give any shader, or the given shader does not work
#	define VERTEX_SHADER_DEFAULT "#version 330 core\nlayout (location = 0) in vec3 aPos;\nvoid main()\n{\n   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}\0"
//Same but for fragment shader
#	define FRAGMENT_SHADER_DEFAULT "#version 330 core\nout vec4 FragColor;\nvoid main()\n{\n   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n}\n\0"

//SOME PARAMETERS
#define MAX_ROTATION_SPEED 1
#define INIT_ROTATION_SPEED 0.1
#define INCR_ROTATIONS_SPEED 0.01
#define MOVEMENT_SPEED 0.01


struct Paramters {
	int width;
	int height;
	std::string title;
};

class Window {
	private:
		GLFWwindow* _window = NULL;
		Mesh _mesh;
		Shader _shader;

		void setupShader();
		void gladLoad();
		void loadTexture(std::string path);
		void createMesh(std::string name, Data &data);
		void createWindow(int width, int height, const char* title);

	public:
		Window(Paramters &param, std::string &meshPath, std::string &texturePath);
		~Window();

		void start();

		class WindowCreationException : public std::exception {
			virtual const char* what() const throw() {
				return "Failed to create GLFW window";
			}
		};
		class GladInitializationException : public std::exception {
			virtual const char* what() const throw() {
				return "Failed to initialize GLAD";
			}
		};
};

#endif