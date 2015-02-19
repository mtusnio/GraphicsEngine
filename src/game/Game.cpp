#include "Game.h"

#include <GLFW\glfw3.h>
#include <cmath>

#include "../renderer/OpenGLRenderer.h"

#include "../scene/IScene.h"

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
	End();
}

void Game::Start(GLFWwindow & window)
{
	m_Window = &window;
	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);
	m_StartTime = glfwGetTime();
	glfwSetKeyCallback(m_Window, &Game::GlobalKeyCallback);
	m_Renderer = new OpenGLRenderer(*m_Window);
}

void Game::End()
{
	if (m_Renderer)
	{
		delete m_Renderer;
		m_Renderer = nullptr;
	}
	
	for (IScene * scene : m_Scenes)
	{
		delete scene;
	}
	m_Scenes.clear();
}

void Game::Run()
{
	glfwPollEvents();

	//m_Renderer->RenderScene(nullptr);
}

void Game::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
}