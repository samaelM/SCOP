#include "Window.hpp"

void Window::moveMesh(const float direction, const Axis axis) {
	(void) direction;
	(void) axis;
}

void Window::keyCallbackTrampoline(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (instance) {
        instance->processInput(key, scancode, action, mods);
	}
}

void Window::processInput(int key, int scancode, int action, int mods) {
	(void)scancode;
	(void)mods;
	(void)action;
	switch (key)
	{
	case GLFW_KEY_LEFT_CONTROL:
		break;
	//
	case GLFW_KEY_ESCAPE:
		std::cout << "should close" << std::endl;
		glfwSetWindowShouldClose(this->_window, true);
		break;
	case GLFW_KEY_SPACE:
		if (action == GLFW_RELEASE)
			this->_mesh->changeTexture();
		break;
	case GLFW_KEY_G:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case GLFW_KEY_F:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	//
	case GLFW_KEY_LEFT:
		this->_mesh->move(-1, Axis::X, this->_deltaTime);
		break;
	case GLFW_KEY_RIGHT:
		this->_mesh->move(1, Axis::X, this->_deltaTime);
		break;
	case GLFW_KEY_UP:
 		this->_mesh->move(1, Axis::Y, this->_deltaTime);
		break;
	case GLFW_KEY_DOWN:
		this->_mesh->move(-1, Axis::Y, this->_deltaTime);
		break;
	//
	case GLFW_KEY_W:
		this->_mesh->move(-1, Axis::Z, this->_deltaTime);
		break;
	case GLFW_KEY_A:
		this->_mesh->rotate(1, Axis::Z, this->_deltaTime);
		break;
	case GLFW_KEY_S:
		this->_mesh->move(1, Axis::Z, this->_deltaTime);
		break;
	case GLFW_KEY_D:
		this->_mesh->rotate(-1, Axis::Z, this->_deltaTime);
		break;
	//
	case GLFW_KEY_I:
		this->_mesh->rotate(-1, Axis::X, this->_deltaTime);
		break;
	case GLFW_KEY_J:
		this->_mesh->rotate(-1, Axis::Y, this->_deltaTime);
		break;
	case GLFW_KEY_K:
		this->_mesh->rotate(1, Axis::X, this->_deltaTime);
		break;
	case GLFW_KEY_L:
		this->_mesh->rotate(1, Axis::Y, this->_deltaTime);
		break;
	//
	default:
		break;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	(void)window;
	glViewport(0, 0, width, height);
}

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
	if (!glfwInit()) {
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	this->_window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (this->_window == NULL) {
		glfwTerminate();
		throw WindowCreationException();
	}
	std::cout << "Successfully created window (" << width << "|" << height << ")" << std::endl;

	glfwMakeContextCurrent(this->_window);
	glfwSetFramebufferSizeCallback(this->_window, framebuffer_size_callback);
	glfwSetWindowUserPointer(this->_window, this);
    glfwSetKeyCallback(this->_window, Window::keyCallbackTrampoline);

	this->gladLoad();
}

void Window::gladLoad() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw GladInitializationException();
	}

	std::cout << "Successfully initialized GLAD" << std::endl;
}

void Window::loadMesh(const std::string &path) {
	MeshData data = Parser::getMeshData(path);
	data.normalizeVertices();
	this->_mesh = new Mesh(data.getVertices(), data.getFaces());

	std::cout << "Successfully loaded Mesh in memory (";
	std::cout << std::to_string(this->_mesh->nbVertices());
	std::cout << " vertices|" << std::to_string(this->_mesh->nbFaces());
	std::cout << " faces) from file : `" << path << "`" << std::endl;
}

void Window::loadTexture(const std::string &path) {
	std::optional<TextureData> optdata = Parser::getTextureData(path);
	if (!optdata.has_value()) {
		throw std::out_of_range("data coult not been parsed, aborting");
	}
	TextureData &data = optdata.value(); 
	this->_texture = new Texture(data._pixels, data._height, data._width);

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

	this->_mesh->prepare(this->_shader);

	std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
	this->_mesh->changeTexture();

	while (!glfwWindowShouldClose(this->_window)) {
		glfwPollEvents();

		auto currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<float> elapsed = currentTime - lastTime;
		this->_deltaTime = elapsed.count();
		if (this->_deltaTime < 0.0f) this->_deltaTime = 0.0f;
		if (this->_deltaTime > 0.1f) this->_deltaTime = 0.1f;
		lastTime = currentTime;

		glClearColor(0.3f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(this->_shader.getShader());

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
