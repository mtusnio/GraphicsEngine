#include "EntitySystem.h"

EntitySystem::EntitySystem()
{
	m_Scene = nullptr;
	m_LastID = Entity::INVALID_ID + 1;
}

EntitySystem::~EntitySystem()
{
	for (auto entry : m_Entities)
	{
		_ASSERT(entry.second != nullptr);

		delete entry.second;
	}


}
Entity * EntitySystem::FindEntityByID(Entity::ID id) const
{
	if (id == Entity::INVALID_ID)
		return nullptr;

	auto it = m_Entities.find(id);
	if (it != m_Entities.end())
		return it->second;

	return nullptr;
}

Entity::ID EntitySystem::AddEntity(Entity * pEnt)
{
	_ASSERT(pEnt != nullptr);

	if (pEnt->GetEntitySystem() == this)
		return pEnt->GetID();

	DetachEntity(pEnt);

	pEnt->SetEntitySystem(this);
	pEnt->SetID(GenerateID());

	m_Entities[pEnt->GetID()] = pEnt;

	return pEnt->GetID();
}

bool EntitySystem::RemoveEntity(Entity * pEnt, bool shouldDelete)
{
	_ASSERT(pEnt != nullptr);

	if (pEnt->GetEntitySystem() != this)
		return false;

	_ASSERT(FindEntityByID(pEnt->GetID()) != nullptr);

	DetachEntity(pEnt);

	if (shouldDelete)
		delete pEnt;

	return true;
}

const std::unordered_map<Entity::ID, Entity*> & EntitySystem::GetEntities() const
{
	return m_Entities;
}

Entity::ID EntitySystem::GenerateID()
{
	Entity::ID ret = m_LastID;
	m_LastID++;

	return ret;
}

void EntitySystem::DetachEntity(Entity * pEnt)
{
	IEntitySystem * system = pEnt->GetEntitySystem();

	if (system != this)
		system->RemoveEntity(pEnt);
	else
		m_Entities.erase(pEnt->GetID());
	pEnt->SetEntitySystem(nullptr);
	pEnt->SetID(Entity::INVALID_ID);
}