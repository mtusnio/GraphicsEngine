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
	entity->SetPosition(Vector(6.0f, -1.0f, -1.0f));
	scene->GetEntitySystem().AddEntity(*entity);
}