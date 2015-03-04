#include "Game.h"

#include "../renderer/OpenGL/OpenGLHeader.h"
#include <cmath>
#include <iostream>
#include <algorithm>

#include "../renderer/OpenGL/OpenGLRenderer.h"
#include "../renderer/OpenGL/OpenGLTexture.h"
#include "../renderer/OpenGL/OpenGLShader.h"

#include "../scene/IScene.h"


Game::Game() : 
m_ModelManager(*this)
{
	m_TextureManager = new LoadablesManager<OpenGLTexture, Texture>(*this);
	m_ShaderManager = new LoadablesManager<OpenGLShader, Shader>(*this);
	m_Window = nullptr;

}

Game::~Game()
{
	if (m_TextureManager)
		delete m_TextureManager;

	if (m_ShaderManager)
		delete m_ShaderManager;

	ClearContent();
}

void Game::Start(GLFWwindow & window)
{
	m_Window = &window;
	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);
	m_Renderer = new OpenGLRenderer(*this);

	m_Time.GameTime = 0;

	// Set some basic delta to avoid divisions by zero
	m_Time.Delta = 0.1f;
	glfwSetTime(0.0f);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::string error = std::string((const char*)glewGetErrorString(err));
		Log(error);
		exit(EXIT_FAILURE);
	}
}

void Game::End()
{
	ClearContent();
}

void Game::Run()
{
	glfwPollEvents();

	HandleInput();

	for (IScene * scene : m_Scenes)
		scene->SimulatePreFrame();

	if (m_Scenes.size() > 0)
		m_Renderer->RenderScene(*m_Scenes[0], GetRenderPosition(), GetRenderAngle());

	for (IScene * scene : m_Scenes)
		scene->SimulatePostFrame();

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

void Game::Log(const std::string & msg)
{
	std::cout << msg << std::endl;
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

Vector Game::GetRenderPosition() const
{
	return Vector(0, 0, 0);
}

Angle Game::GetRenderAngle() const
{
	return Angle(0, 0, 0);
}