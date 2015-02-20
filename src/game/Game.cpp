#include "Game.h"

#include <GLFW\glfw3.h>
#include <cmath>

#include <algorithm>

#include "../renderer/OpenGL/OpenGLRenderer.h"

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
	ClearContent();
}

void Game::Start(GLFWwindow & window)
{
	m_Window = &window;
	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(m_Window, &Game::GlobalKeyCallback);
	m_Renderer = new OpenGLRenderer(*m_Window);

	m_Time.GameTime = 0;

	// Set some basic delta to avoid divisions by zero
	m_Time.Delta = 0.1f;
	glfwSetTime(0.0f);
}

void Game::End()
{
	ClearContent();
}

void Game::Run()
{
	glfwPollEvents();

	if (m_Scenes.size() > 0)
		m_Renderer->RenderScene(*m_Scenes[0], Vector(0, 0, 0), Angle(0, 0, 0));

	// Update timers
	double cur = glfwGetTime();
	m_Time.Delta = (float)(cur - m_Time.GameTime);
	m_Time.GameTime += m_Time.Delta;
}

void Game::AddScene(IScene * scene)
{
	if (std::find(m_Scenes.begin(), m_Scenes.end(), scene) == m_Scenes.end())
		m_Scenes.push_back(scene);
}
void Game::RemoveScene(IScene * scene)
{
	m_Scenes.erase(std::remove(m_Scenes.begin(), m_Scenes.end(), scene), m_Scenes.end());
}

const std::vector<IScene*> & Game::GetScenes() const
{
	return m_Scenes;
}


void Game::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
}

void Game::ClearContent()
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