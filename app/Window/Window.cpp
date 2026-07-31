#include "Window.hpp"

void Window::processInput(GLFWwindow *window)
{// mettre dans un switch case?
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
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			this->_mesh->rotate(1, Axis::X, this->_deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			this->_mesh->rotate(-1, Axis::X, this->_deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			this->_mesh->rotate(1, Axis::Y, this->_deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			this->_mesh->rotate(-1, Axis::Y, this->_deltaTime);
		}
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			this->_mesh->move(1, Axis::Z, this->_deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			this->_mesh->move(-1, Axis::Z, this->_deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			this->_mesh->rotate(1, Axis::Z, this->_deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			this->_mesh->rotate(-1, Axis::Z, this->_deltaTime);
		}
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		this->_mesh->move(1, Axis::X, this->_deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		this->_mesh->move(-1, Axis::X, this->_deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		this->_mesh->move(1, Axis::Y, this->_deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		this->_mesh->move(-1, Axis::Y, this->_deltaTime);
	}
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

	if (this->_window == NULL) {
		glfwTerminate();
		throw WindowCreationException();
	}
	std::cout << "Successfully created window" << std::endl;

	glfwMakeContextCurrent(this->_window);
	glfwSetFramebufferSizeCallback(this->_window, framebuffer_size_callback);

	this->gladLoad();
}

void Window::gladLoad() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw GladInitializationException();
	}

	std::cout << "Successfully initialized GLAD" << std::endl;
}

void Window::loadMesh(const std::string &path) {
	Data data = Parser::getData(path);
	data.normalizeVertices();
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

	// void (*)(GLFWwindow *window, int key, int scancode, int action, int mods)"
	// glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods){;});
	// glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods){;});
	this->_mesh->prepare(this->_shader);

	std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();

	while (!glfwWindowShouldClose(this->_window)) {
		glfwPollEvents();
		this->processInput(this->_window);

		//inline func?
		auto currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<float> elapsed = currentTime - lastTime;
		this->_deltaTime = elapsed.count();
		if (this->_deltaTime < 0.0f) this->_deltaTime = 0.0f;
		if (this->_deltaTime > 0.1f) this->_deltaTime = 0.1f;
		lastTime = currentTime;

		glClearColor(0.3f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(this->_shader.getShader());

		// this->_mesh->rotate(Direction::LEFT, this->_deltaTime);
		this->_mesh->show();

		

		glBindVertexArray(this->_mesh->getVAO());
		glDrawElements(GL_TRIANGLES, this->_mesh->nbFaces(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(this->_window);
	}
}

Window::~Window(){
	if (this->_window)
		glfwDestroyWindow(this->_window);
	delete this->_mesh;
	glfwTerminate();
}
