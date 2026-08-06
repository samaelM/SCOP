#include "Window/Window.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE "SCOP"

#define VERTEX_SHADER_FILE "ressources/shaders/default.vert"
#define FRAGMENT_SHADER_FILE "ressources/shaders/default.frag"
// #define TEXTURE_FILE "ressources/textures/img.tga"
#define HELP "usage: ./SCOP mesh.obj texture.tga\n"
// #define OBJECT_FILE "ressources/objects/."

int main(int argc, char const *argv[])
{
	if (argc != 3) {
		std::cout << HELP << std::endl;
		return 1;
	}
	try
	{
		Paramters param({WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE});
		Window app(param, VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE, argv[1], argv[2]);

		app.start();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}
