#ifndef H_ENTITYSYSTEM
#define H_ENTITYSYSTEM


#include "IEntitySystem.h"

class EntitySystem : public IEntitySystem
{
public:
	EntitySystem();
	virtual ~EntitySystem();

	virtual IScene * GetScene() const { return m_Scene;  }
	virtual void SetScene(IScene * scene) { m_Scene = scene;  }

	virtual Entity * FindEntityByID(Entity::ID id);

	virtual Entity * CreateEntity();
	virtual bool RemoveEntity(Entity & pEnt);

	virtual const std::unordered_map<Entity::ID, Entity> & GetEntities() const;

private:
	Entity::ID GenerateID();

	std::unordered_map<Entity::ID, Entity> m_Entities;
	IScene * m_Scene;

	Entity::ID m_LastID;
};


#endif