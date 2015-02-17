
#include <GLFW\glfw3.h>
#include <cstdlib>
#include <iostream>
#include <string>
void error_callback(int error, const char * description)
{
	std::cerr << description << std::endl;
}

int main(int argc, char ** argv)
{
	if (!glfwInit())
		return EXIT_FAILURE;
	glfwSetErrorCallback(error_callback);

	int width = 640;
	int height = 480;

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

	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();


	}


	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}