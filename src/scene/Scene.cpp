#include "Scene.h"

#include <algorithm>

Scene::Scene(IGame & game) :
m_ParentGame(&game),
m_CollisionManager(*this)
{
	
}

Scene::~Scene()
{

}

void Scene::SimulatePreFrame()
{
	m_CollisionManager.Run();
}

void Scene::SimulatePostFrame()
{

}

void Scene::RegisterLight(const LightSource & light, LightSource::Type type)
{
	if (HasLightSource(light))
		return;

	if (m_LightSources.find(type) == m_LightSources.end())
		m_LightSources[type] = std::vector<const LightSource*>();

	m_LightSources[type].push_back(&light);
}

void Scene::UnregisterLight(const LightSource & light)
{
	if (!HasLightSource(light))
		return;

	for (auto it = m_LightSources.begin(); it != m_LightSources.end(); it++)
	{
		it->second.erase(std::remove(it->second.begin(), it->second.end(), &light));
	}
		
}

bool Scene::HasLightSource(const LightSource & light) const
{
	for (auto pair : m_LightSources)
	{
		if (std::find(pair.second.begin(), pair.second.end(), &light) != pair.second.end())
			return true;
	}
		
	
	return false;
}

std::vector<const LightSource*> Scene::GetLightSources(LightSource::Type type) const
{
	if (m_LightSources.find(type) == m_LightSources.end())
		return std::vector<const LightSource*>();

	return m_LightSources.at(type);
}