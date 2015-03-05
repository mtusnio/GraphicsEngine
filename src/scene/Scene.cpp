#include "Scene.h"

#include <algorithm>

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

void Scene::RegisterLight(const LightSource & light)
{
	if (HasLightSource(light))
		return;

	m_LightSources.push_back(&light);
}

void Scene::UnregisterLight(const LightSource & light)
{
	if (!HasLightSource(light))
		return;

	m_LightSources.erase(std::remove(m_LightSources.begin(), m_LightSources.end(), &light));
}

bool Scene::HasLightSource(const LightSource & light) const
{
	return std::find(m_LightSources.begin(), m_LightSources.end(), &light) != m_LightSources.end();
}

std::vector<const LightSource*> Scene::GetLightSources() const
{
	return m_LightSources;
}