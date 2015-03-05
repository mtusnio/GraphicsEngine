#include "../renderer/OpenGL/OpenGLHeader.h"

#include <cstdlib>
#include <iostream>
#include <string>

#include "../game/CustomGame.h"

void error_callback(int error, const char * description)
{
	std::cerr << description << std::endl;
}

int main(int argc, char ** argv)
{
	if (!glfwInit())
		return EXIT_FAILURE;
	glfwSetErrorCallback(error_callback);

	int width = 1440;
	int height = 900;

	if (argc >= 3)
	{
		width = std::stoi(argv[1]);
		height = std::stoi(argv[2]);
	}

	GLFWwindow * window = glfwCreateWindow(width, height, "OpenGL Engine", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	

	CustomGame game;
	game.Start(*window);
	while (!glfwWindowShouldClose(window))
	{
		game.Run();
	}
	game.End();

	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}