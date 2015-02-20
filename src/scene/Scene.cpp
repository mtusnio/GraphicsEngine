#include "Scene.h"

Scene::Scene(IGame & game)
{
	m_ParentGame = &game;
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