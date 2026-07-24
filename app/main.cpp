#include "Window/Window.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE "SCOP"

int main(int argc, char const *argv[])
{
	if (argc != 2) {
		// print help
		return 1;
	}
	try
	{
		Paramters param({WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE});
		Window app(param, "vert", "frag", "mesh", "text");

		app.start();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}
