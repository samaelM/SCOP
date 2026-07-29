#include "Window.hpp"

void Window::processInput(GLFWwindow *window)
{// mettre dans un switch case?
	// if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
	// 	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
	// 		dz -= MOVEMENT_SPEED;
	// 	}
	// 	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
	// 		dz += MOVEMENT_SPEED;
	// 	}
	// }
	// else {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			std::cout << "should close" << std::endl;
			glfwSetWindowShouldClose(window, true);
		}
		
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		// if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		// 	std::cout << std::to_string(angle) <<std::endl;
		// }

		// if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		// 	dx += MOVEMENT_SPEED;
		// }
		// if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		// 	dx -= MOVEMENT_SPEED;
		// }
		// if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		// 	dy += MOVEMENT_SPEED;
		// }
		// if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		// 	dy -= MOVEMENT_SPEED;
		// }

		// if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) {
		// 	rotation_speed = (rotation_speed - INCR_ROTATIONS_SPEED > 0.0)? rotation_speed - INCR_ROTATIONS_SPEED: rotation_speed;
		// 	std::cout << "new rotation speed: " << rotation_speed << std::endl;
		// 	if (rotation_speed < INCR_ROTATIONS_SPEED) rotation_speed = 0;
		// }
		// if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) {
		// 	rotation_speed = (rotation_speed + INCR_ROTATIONS_SPEED <= MAX_ROTATION_SPEED)? rotation_speed + INCR_ROTATIONS_SPEED: rotation_speed;
		// 	std::cout << "new rotation speed: " << rotation_speed << std::endl;
		// }
		
		// if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
		// 	b_turning = !b_turning;
		// }
	// }
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

//CLASS MEMBER FUNCTIONS
Window::Window(	const Paramters &param,
				const std::string &vertShPath,
				const std::string &fragShPath,
				const std::string &meshPath,
				const std::string &texturePath) {

	this->init(param.width, param.height, param.title.c_str());
	this->loadMesh(meshPath);
	this->loadTexture(texturePath);
	this->loadShaders(vertShPath, fragShPath);
	std::cout << "Window initialated" <<std::endl;
}


void Window::init(const int &width, const int &height, const char* title) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	this->_window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (this->_window == NULL)
	{
		glfwTerminate();
		throw WindowCreationException();
	}
	std::cout << "Successfully created window" << std::endl;

	glfwMakeContextCurrent(this->_window);
	glfwSetFramebufferSizeCallback(this->_window, framebuffer_size_callback);

	this->gladLoad();
}

void Window::gladLoad() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw GladInitializationException();
	}
	std::cout << "Successfully initialized GLAD" << std::endl;
}

void Window::loadMesh(const std::string &path) {
	std::cout << "loading mesh..." <<std::endl;
	Data data = Parser::getData(path);
	this->_mesh = new Mesh(data.getVertices(), data.getFaces());
	std::cout << "Successfully loaded Mesh in memory (";
	std::cout << std::to_string(this->_mesh->nbVertices());
	std::cout << " vertices|" << std::to_string(this->_mesh->nbFaces());
	std::cout << " faces) from file : `" << path << "`" << std::endl;
}

void Window::loadTexture(const std::string &path) {
	this->_texture = Texture(path);
	std::cout << "Successfully loaded Texture in memory ";
	std::cout << " from file : `" << path << "`" << std::endl;
}

void Window::loadShaders(const std::string &vertShPath, const std::string &fragShPath) {
	this->_shader = Shader(vertShPath, fragShPath);
	std::cout << "Successfully loaded Shaders in memory ";
	std::cout << " from files : `" << vertShPath << "` and `";
	std::cout << fragShPath << "`" << std::endl;
}

void Window::start() {
	std::cout << "App launched!\n";
	glEnable(GL_DEPTH_TEST);
	// GLuint dx_uniform = glGetUniformLocation(this->_shader.getShader(), "dx");
	// GLuint dy_uniform = glGetUniformLocation(this->_shader.getShader(), "dy");
	// GLuint dz_uniform = glGetUniformLocation(this->_shader.getShader(), "dz");
	// GLuint m_model_uniform = glGetUniformLocation(this->_shader.getShader(), "m_model");
	// GLuint m_projection_uniform = glGetUniformLocation(this->_shader.getShader(), "m_projection");
	// GLuint m_view_uniform = glGetUniformLocation(this->_shader.getShader(), "m_view");

	float angle = 0.0f;
	GLfloat m_projection[16] = {
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	GLfloat m_model[16] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	// void (*)(GLFWwindow *window, int key, int scancode, int action, int mods)"
	// glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods){;});
	// glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods){;});

	std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();

	while (!glfwWindowShouldClose(this->_window)) {
		GLfloat m_view[16] = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		glfwPollEvents();
		this->processInput(this->_window);

		auto currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<float> elapsed = currentTime - lastTime;
		float deltaTime = elapsed.count();
		
		if (deltaTime < 0.0f) deltaTime = 0.0f;
		if (deltaTime > 0.1f) deltaTime = 0.1f;
		
		lastTime = currentTime;

		glClearColor(0.3f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(this->_shader.getShader());

		// // if (b_turning) {
			// angle += 2.0f * static_cast<float>(M_PI) * 0.5 * deltaTime;
			// angle = std::fmod(angle, 2.0f * static_cast<float>(M_PI));

			// m_model[0] = cos(angle);
			// m_model[2] = sin(angle);
			// m_model[8] = -sin(angle);
			// m_model[10] = cos(angle); 
		// // }

		// // perspective(m_projection, M_PI / 2, 800/800, 0.1f, 100.0f);
		// GLfloat vec[3] = {0.0f, 0.0f, -3.0f};
		// // translate(m_view, vec);

		// // glUniform1f(dx_uniform, dx);
		// // glUniform1f(dy_uniform, dy);
		// // glUniform1f(dz_uniform, dz);
		// glUniformMatrix4fv(m_model_uniform, 1, GL_FALSE, m_model);
		// glUniformMatrix4fv(m_projection_uniform, 1, GL_FALSE, m_projection);
		// glUniformMatrix4fv(m_view_uniform, 1, GL_FALSE, m_view);

		glBindVertexArray(this->_mesh->getVAO());
		glDrawElements(GL_TRIANGLES, this->_mesh->nbFaces(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(this->_window);
	}
}

Window::~Window(){
	if (this->_window)
		glfwDestroyWindow(this->_window);
	glfwTerminate();
}
