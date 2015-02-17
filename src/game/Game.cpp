#include "Game.h"
#include <GLFW\glfw3.h>

Game * Game::InputHandler = nullptr;

void Game::GlobalKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (InputHandler)
		InputHandler->KeyCallback(window, key, scancode, action, mods);
}

Game::Game()
{
	m_Window = nullptr;
}

Game::~Game()
{
}

void Game::Start(GLFWwindow * window)
{
	m_Window = window;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	m_StartTime = glfwGetTime();
	glfwSetKeyCallback(window, &Game::GlobalKeyCallback);
}

void Game::End()
{
	
}

void Game::Run()
{
	glfwPollEvents();
}

void Game::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
}