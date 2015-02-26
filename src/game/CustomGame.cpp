#include "CustomGame.h"

#include <GLFW\glfw3.h>
#include <cmath>

#include "../scene/Scene.h"

CustomGame::CustomGame()
{
}

CustomGame::~CustomGame()
{
	m_PrevX = 0;
	m_PrevY = 0;
}

void CustomGame::Start(GLFWwindow & window)
{
	Game::Start(window);

	glfwGetCursorPos(&window, &m_PrevX, &m_PrevY);

	Scene * scene = new Scene(*this);

	AddScene(scene);

	std::shared_ptr<const Model> ptr = GetModelManager().Cache("models/sponza.obj");

	_ASSERT(ptr.get() != nullptr);

	Entity * entity = new Entity();

	entity->SetModel(ptr);
	entity->SetPosition(Vector(4.0f, -1.0f, -1.0f));
	entity->SetRotation(Angle(90, 0, 0));
	scene->GetEntitySystem().AddEntity(*entity);

	glfwSetInputMode(&window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void CustomGame::HandleInput()
{
	GLFWwindow * window = GetWindow();
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	const float SPEED = 4.0f;
	const float ROT_SPEED = 8.0f;

	double xDiff = xpos - m_PrevX;
	double yDiff = ypos - m_PrevY;

	m_PrevX = xpos;
	m_PrevY = ypos;

	float delta = GetTime().Delta;
	m_RenderAngle.y += delta * ROT_SPEED * (float)-yDiff;
	m_RenderAngle.z += delta * ROT_SPEED * (float)-xDiff;

	m_RenderAngle.y = fmax(-89.0f, fmin(89.0f, m_RenderAngle.y));

	Vector dir = m_RenderAngle.ToDirection();
	// Handle keys
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		m_RenderPosition += dir * delta * SPEED;
	}
	else if (glfwGetKey(window, GLFW_KEY_S))
	{
		m_RenderPosition -= dir * delta * SPEED;
	}

	Vector left = dir.Left();
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		m_RenderPosition += left * delta * SPEED;
	}
	else if (glfwGetKey(window, GLFW_KEY_D))
	{
		m_RenderPosition -= left * delta * SPEED;
	}
}