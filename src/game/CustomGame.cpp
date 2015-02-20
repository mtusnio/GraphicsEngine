#include "CustomGame.h"
#include "../scene/Scene.h"
void CustomGame::Start(GLFWwindow & window)
{
	Game::Start(window);

	Scene * scene = new Scene(*this);

	AddScene(scene);

	std::shared_ptr<const Model> ptr = GetModelManager().Cache("models/cube.obj");

	_ASSERT(ptr.get() != nullptr);

	Entity * entity = new Entity();

	entity->SetModel(ptr);
	entity->SetPosition(Vector(4.0f, -1.0f, -1.0f));
	entity->SetRotation(Angle(0, 0, 45));
	scene->GetEntitySystem().AddEntity(*entity);
}