#include "Scene.h"

Scene::Scene(IGame * game)
{
	_ASSERT(game != nullptr);

	m_ParentGame = game;
}

Scene::~Scene()
{

}

void Scene::SimulatePreFrame()
{

}

void Scene::SimulatePostFrame()
{

}