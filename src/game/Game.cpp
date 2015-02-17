#include "Game.h"

#include <GLFW\glfw3.h>
#include <cmath>

#include "../renderer/OpenGLRenderer.h"

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
	m_Renderer = new OpenGLRenderer(m_Window);
}

void Game::End()
{
	if (m_Renderer)
	{
		delete m_Renderer;
		m_Renderer = nullptr;
	}
	
}

void Game::Run()
{
	glfwPollEvents();

	m_Renderer->RenderScene(nullptr);
}

void Game::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
}