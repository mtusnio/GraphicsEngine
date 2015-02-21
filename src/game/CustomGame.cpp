#include "CustomGame.h"
#include "../scene/Scene.h"

#include <GLFW\glfw3.h>

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

	std::shared_ptr<const Model> ptr = GetModelManager().Cache("models/cube.obj");

	_ASSERT(ptr.get() != nullptr);

	Entity * entity = new Entity();

	entity->SetModel(ptr);
	entity->SetPosition(Vector(4.0f, -1.0f, -1.0f));
	entity->SetRotation(Angle(0, 0, 45));
	scene->GetEntitySystem().AddEntity(*entity);

	glfwSetInputMode(&window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void CustomGame::HandleInput()
{
	GLFWwindow * window = GetWindow();
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	const float SPEED = 4.0f;

	double xDiff = xpos - m_PrevX;
	double yDiff = ypos - m_PrevY;

	m_PrevX = xpos;
	m_PrevY = ypos;

	float delta = GetTime().Delta;
	m_RenderAngle.y += delta * SPEED * (float)-yDiff;
	m_RenderAngle.z += delta * SPEED * (float)-xDiff;

	Vector dir = m_RenderAngle.ToDirection();
	// Handle keys
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		m_RenderPosition += dir * delta * SPEED;
	}
	else if (glfwGetKey(window, GLFW_KEY_S))
	{

	}
}