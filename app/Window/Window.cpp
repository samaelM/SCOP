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
	if (action != GLFW_PRESS)
		return;
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(this->_window, true);
		break;
	case GLFW_KEY_SPACE:
		this->_mesh->changeTexture();
		break;
	case GLFW_KEY_G:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case GLFW_KEY_F:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case GLFW_KEY_R:
		this->_camera.reset();
		break;
	default:
		break;
	}
}

void Window::handleInput() {
	GLFWwindow *w = this->_window;
	const float dt = this->_deltaTime;

	if (glfwGetKey(w, GLFW_KEY_LEFT) == GLFW_PRESS)  this->_mesh->move(-1, Axis::X, dt);
	if (glfwGetKey(w, GLFW_KEY_RIGHT) == GLFW_PRESS) this->_mesh->move(1, Axis::X, dt);
	if (glfwGetKey(w, GLFW_KEY_UP) == GLFW_PRESS)    this->_mesh->move(1, Axis::Y, dt);
	if (glfwGetKey(w, GLFW_KEY_DOWN) == GLFW_PRESS)  this->_mesh->move(-1, Axis::Y, dt);
	if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS)     this->_mesh->move(-1, Axis::Z, dt);
	if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS)     this->_mesh->move(1, Axis::Z, dt);

	if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS)     this->_mesh->rotate(1, Axis::Z, dt);
	if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS)     this->_mesh->rotate(-1, Axis::Z, dt);
	if (glfwGetKey(w, GLFW_KEY_I) == GLFW_PRESS)     this->_mesh->rotate(-1, Axis::X, dt);
	if (glfwGetKey(w, GLFW_KEY_K) == GLFW_PRESS)     this->_mesh->rotate(1, Axis::X, dt);
	if (glfwGetKey(w, GLFW_KEY_J) == GLFW_PRESS)     this->_mesh->rotate(-1, Axis::Y, dt);
	if (glfwGetKey(w, GLFW_KEY_L) == GLFW_PRESS)     this->_mesh->rotate(1, Axis::Y, dt);
}

void Window::mouseButtonTrampoline(GLFWwindow* window, int button, int action, int mods) {
	Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (instance)
		instance->onMouseButton(button, action, mods);
}

void Window::onMouseButton(int button, int action, int mods) {
	(void)mods;
	if (button != GLFW_MOUSE_BUTTON_LEFT)
		return;
	if (action == GLFW_PRESS) {
		this->_dragging = true;
		glfwGetCursorPos(this->_window, &this->_lastX, &this->_lastY);
	}
	else if (action == GLFW_RELEASE) {
		this->_dragging = false;
	}
}

void Window::cursorPosTrampoline(GLFWwindow* window, double xpos, double ypos) {
	Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (instance)
		instance->onCursorPos(xpos, ypos);
}

void Window::onCursorPos(double xpos, double ypos) {
	if (!this->_dragging)
		return;
	const double dx = xpos - this->_lastX;
	const double dy = ypos - this->_lastY;
	this->_lastX = xpos;
	this->_lastY = ypos;
	this->_camera.orbit(static_cast<float>(dx), static_cast<float>(dy));
}

void Window::scrollTrampoline(GLFWwindow* window, double xoffset, double yoffset) {
	Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (instance)
		instance->onScroll(xoffset, yoffset);
}

void Window::onScroll(double xoffset, double yoffset) {
	(void)xoffset;
	this->_camera.zoom(static_cast<float>(yoffset));
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
	glfwSetMouseButtonCallback(this->_window, Window::mouseButtonTrampoline);
	glfwSetCursorPosCallback(this->_window, Window::cursorPosTrampoline);
	glfwSetScrollCallback(this->_window, Window::scrollTrampoline);

	this->gladLoad();
}

void Window::gladLoad() {
	if (!gladLoadGL(glfwGetProcAddress)) {
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
		throw std::invalid_argument("data coult not been parsed, aborting");
	}
	TextureData &data = optdata.value(); 
	this->_texture = new Texture(data._pixels, data._height, data._width);

	std::cout << "Successfully loaded Texture in memory ";
	std::cout << " from file : `" << path << "`" << std::endl;
}

void Window::loadShaders(const std::string &vertShPath, const std::string &fragShPath) {
	this->_shader = new Shader(vertShPath, fragShPath);

	std::cout << "Successfully loaded Shaders in memory ";
	std::cout << " from files : `" << vertShPath << "` and `";
	std::cout << fragShPath << "`" << std::endl;
}

void Window::start() {
	std::cout << "App launched!\n";
	glEnable(GL_DEPTH_TEST);

	this->_mesh->prepare(*this->_shader);

	glUseProgram(this->_shader->getShader());
	const GLint texLoc = glGetUniformLocation(this->_shader->getShader(), "ourTexture");
	if (texLoc >= 0)
		glUniform1i(texLoc, 0);
	this->_texture->bind();

	std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();

	while (!glfwWindowShouldClose(this->_window)) {
		glfwPollEvents();

		auto currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<float> elapsed = currentTime - lastTime;
		this->_deltaTime = elapsed.count();
		if (this->_deltaTime < 0.0f) this->_deltaTime = 0.0f;
		if (this->_deltaTime > 0.1f) this->_deltaTime = 0.1f;
		lastTime = currentTime;

		this->handleInput();

		int fbWidth, fbHeight;
		glfwGetFramebufferSize(this->_window, &fbWidth, &fbHeight);
		const float aspect = (fbHeight > 0)
			? static_cast<float>(fbWidth) / static_cast<float>(fbHeight)
			: 1.0f;

		GLfloat projection[16];
		perspective(projection, static_cast<float>(M_PI) / 2.0f, aspect, 0.1f, 100.0f);
		GLfloat view[16];
		this->_camera.getViewMatrix(view);
		this->_mesh->setProjection(projection);
		this->_mesh->setView(view);

		glClearColor(0.3f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(this->_shader->getShader());

		this->_mesh->show(this->_deltaTime);

		glBindVertexArray(this->_mesh->getVAO());
		glDrawElements(GL_TRIANGLES, this->_mesh->nbFaces(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(this->_window);
	}
}

Window::~Window(){
	if (this->_window)
		glfwDestroyWindow(this->_window);
	if (this->_mesh)
		delete this->_mesh;
	if (this->_texture)
		delete this->_texture;
	if (this->_shader)
		delete this->_shader;
	glfwTerminate();
}
