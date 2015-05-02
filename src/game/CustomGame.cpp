#include "CustomGame.h"

#include "../renderer/OpenGL/OpenGLHeader.h"
#include <cmath>

#include "../scene/Scene.h"

CustomGame::CustomGame()
{
	m_Light.Color[0] = 1.f;
	m_Light.Color[1] = 1.f;
	m_Light.Color[2] = 1.f;
	m_Light.Attenuation.Constant = 0.0f;
	m_Light.Attenuation.Linear = 0.05f;
	m_Light.Attenuation.Quadratic = 0.f;
	m_Light.Exponent = 8.0f;
	m_Light.Cone = 140.0f;
	m_Light.MaxDistance = 128.f;

	_ASSERT(m_KeyLights.size() <= 3);

	for (size_t i = 0; i < m_KeyLights.size(); i++)
	{
		auto & light = m_KeyLights[i];
		light = m_Light;
		light.Color[0] = 0.0f;
		light.Color[1] = 0.0f;
		light.Color[2] = 0.0f;
		light.Color[i] = 1.0f;
	}
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

	// Create first scene
	AddScene(scene);
	scene->RegisterLight(m_Light, LightSource::Type::SPOT);
	std::shared_ptr<const Model> ptr = GetModelManager().Cache("models/sibenik.obj");

	_ASSERT(ptr.get() != nullptr);

	Entity * entity = new Entity();

	entity->SetModel(ptr);
	entity->SetPosition(Vector(0, 0, -2.0f));
	scene->GetEntitySystem().AddEntity(*entity);

	// Create second scene
	scene = new Scene(*this);

	AddScene(scene);

	ptr = GetModelManager().Cache("models/plane.obj");
	entity = new Entity();

	entity->SetModel(ptr);
	entity->SetPosition(Vector(0, 0, -4.0f));
	scene->GetEntitySystem().AddEntity(*entity);

	entity = new Entity();

	entity->SetModel(ptr);
	entity->SetPosition(Vector(0, 0, 8.0f));
	entity->SetPhysicsEnabled(true);
	scene->GetEntitySystem().AddEntity(*entity);

	// Create third scene
	scene = new Scene(*this);

	AddScene(scene);

	ptr = GetModelManager().Cache("models/sponza.obj");
	entity = new Entity();

	entity->SetModel(ptr);
	entity->SetPosition(Vector(0, 0, -4.0f));
	scene->GetEntitySystem().AddEntity(*entity);


	glfwSetInputMode(&window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void CustomGame::End()
{
	auto scenes = GetScenes();

	if (scenes.size() > 0)
		scenes[0]->UnregisterLight(m_Light);
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

	if (!glfwGetKey(window, GLFW_KEY_SPACE))
	{
		m_Light.Position = m_RenderPosition;
		m_Light.Rotation = m_RenderAngle;
	}

	bool control = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) != 0;
	int key = -1;

	if (glfwGetKey(window, GLFW_KEY_1))
		key = 0;
	else if (glfwGetKey(window, GLFW_KEY_2))
		key = 1;
	else if (glfwGetKey(window, GLFW_KEY_3))
		key = 2;

	IScene * scene = GetActiveScene();
	if (key != -1)
	{
		
		if (control)
			scene->UnregisterLight(m_KeyLights[key]);
		else
		{
			scene->RegisterLight(m_KeyLights[key], LightSource::SPOT);
			m_KeyLights[key].Position = m_RenderPosition;
			m_KeyLights[key].Rotation = m_RenderAngle;
		}
	}

	static bool enter = false;
	if (glfwGetKey(window, GLFW_KEY_ENTER) && !enter)
	{
		if (scene->HasLightSource(m_Light))
			scene->UnregisterLight(m_Light);
		else
			scene->RegisterLight(m_Light, LightSource::SPOT);
		enter = true;
	}
	else if (!glfwGetKey(window, GLFW_KEY_ENTER))
		enter = false;

	std::array<int, 3> keyToScene = {
		GLFW_KEY_I,
		GLFW_KEY_O,
		GLFW_KEY_P
	};

	for (size_t i = 0; i < keyToScene.size(); i++)
	{
		if (GetActiveSceneIndex() != i && glfwGetKey(window, keyToScene[i]))
		{
			GetActiveScene()->UnregisterLight(m_Light);
			for (LightSource & light : m_KeyLights)
				GetActiveScene()->UnregisterLight(light);

			SetActiveScene(i);

			GetActiveScene()->RegisterLight(m_Light, LightSource::SPOT);

			m_RenderPosition = Vector();
			m_RenderAngle = Angle();
			break;
		}
	}

		
}