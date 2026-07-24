#include "Window.hpp"

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
}


void Window::init(const int &width, const int &height, const char* title) {
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
	this->_mesh = new Mesh(path);
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
	// GLuint dy_uniform = glGetUniformLocation(shader.getShader(), "dy");
	// GLuint dz_uniform = glGetUniformLocation(shader.getShader(), "dz");
	// GLuint m_model_uniform = glGetUniformLocation(shader.getShader(), "m_model");
	// GLuint m_projection_uniform = glGetUniformLocation(shader.getShader(), "m_projection");
	// GLuint m_view_uniform = glGetUniformLocation(shader.getShader(), "m_view");

	;
}

Window::~Window(){
	if (this->_window)
		glfwDestroyWindow(this->_window);
	glfwTerminate();
}
