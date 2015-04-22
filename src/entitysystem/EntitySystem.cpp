#include "EntitySystem.h"

EntitySystem::EntitySystem()
{
	m_Scene = nullptr;
	m_LastID = Entity::INVALID_ID + 1;

	m_Entities.reserve(100);
}

EntitySystem::~EntitySystem()
{

}

Entity * EntitySystem::FindEntityByID(Entity::ID id)
{
	if (id == Entity::INVALID_ID)
		return nullptr;

	auto it = m_Entities.find(id);
	if (it != m_Entities.end())
		return &it->second;

	return nullptr;
}

Entity * EntitySystem::CreateEntity()
{
	Entity::ID id = GenerateID();

	m_Entities.insert({ id, Entity() });

	m_Entities[id].SetEntitySystem(this);
	m_Entities[id].SetID(id);

	return &m_Entities[id];
}

bool EntitySystem::RemoveEntity(Entity & pEnt)
{
	if (pEnt.GetEntitySystem() != this)
		return false;

	_ASSERT(FindEntityByID(pEnt.GetID()) != nullptr);

	m_Entities.erase(pEnt.GetID());

	return true;
}

const std::unordered_map<Entity::ID, Entity> & EntitySystem::GetEntities() const
{
	return m_Entities;
}

Entity::ID EntitySystem::GenerateID()
{
	Entity::ID ret = m_LastID;
	m_LastID++;

	return ret;
}
