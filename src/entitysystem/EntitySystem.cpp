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

std::vector<Entity*> EntitySystem::GetEntities() const
{
	std::vector<Entity*> ents;
	ents.reserve(m_Entities.size());
	for (auto p : m_Entities)
	{
		ents.push_back(p.second);
	}
	return ents;
}

Entity::ID EntitySystem::GenerateID()
{
	Entity::ID ret = m_LastID;
	m_LastID++;

	return ret;
}

void EntitySystem::DetachEntity(Entity * pEnt) const
{
	IEntitySystem * system = pEnt->GetEntitySystem();

	_ASSERT(system != this);

	system->RemoveEntity(pEnt);
	pEnt->SetEntitySystem(nullptr);
	pEnt->SetID(Entity::INVALID_ID);
}