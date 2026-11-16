#ifndef SCOP_WINDOW_HPP
#	define SCOP_WINDOW_HPP

#	include "../../ressources/lib/glad/include/glad/gl.h"	//Used to find opengl functions and types
#	include "../Graphics/Graphics.hpp"						//Used for the Mesh, Texture and Shader classes
#	include "../Parser/Parser.hpp"							//Used to parse .obj file

#	include <iostream>										//Used to print info on the stdout
#	include <exception>										//Used for throwing exceptions
#	include <chrono>										//Used to calculate delta time
#	include <GLFW/glfw3.h>									//Used to the window

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
		Mesh *_mesh = NULL;
		Texture *_texture = NULL;
		Shader *_shader = NULL;

		Camera _camera;
		bool _dragging = false;
		double _lastX = 0.0;
		double _lastY = 0.0;

		float _deltaTime = 0.0f;

		void init(const int &width, const int &height, const char* title);
		void gladLoad();
		void loadMesh(const std::string &path);
		void loadTexture(const std::string &path);
		void loadShaders(const std::string &vertShPath, const std::string &fragShPath);
		void handleInput();

	public:
		Window(	const Paramters &param,
				const std::string &vertShPath,
				const std::string &fragShPath,
				const std::string &meshPath,
				const std::string &texturePath);
		~Window();

		void start();
		void moveMesh(const float direction, const Axis axis);

		static void keyCallbackTrampoline(GLFWwindow* window, int key, int scancode, int action, int mods);
		void processInput(int key, int scancode, int action, int mods);

		static void mouseButtonTrampoline(GLFWwindow* window, int button, int action, int mods);
		void onMouseButton(int button, int action, int mods);
		static void cursorPosTrampoline(GLFWwindow* window, double xpos, double ypos);
		void onCursorPos(double xpos, double ypos);
		static void scrollTrampoline(GLFWwindow* window, double xoffset, double yoffset);
		void onScroll(double xoffset, double yoffset);

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
