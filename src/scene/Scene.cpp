#include "Scene.h"

#include "../game/IGame.h"

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
	auto entities = m_EntitySystem.GetEntities();

	Time time = m_ParentGame->GetTime();

	for (auto pair : entities)
	{
		Entity * ent = pair.second;
		
		if (!ent->ShouldUsePhysics())
			continue;

		ent->SetPosition(ent->GetPosition() + ent->GetVelocity() * time.Delta);
		
		ent->AddVelocity(Vector(0, 0, -3) * time.Delta);
	}
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