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

	virtual Entity * FindEntityByID(Entity::ID id) const;

	

	virtual Entity::ID AddEntity(Entity * pEnt);
	virtual bool RemoveEntity(Entity * pEnt, bool shouldDelete = true);

	virtual const std::unordered_map<Entity::ID, Entity*> & GetEntities() const;

private:
	Entity::ID GenerateID();
	void DetachEntity(Entity * pEnt);

	std::unordered_map<Entity::ID, Entity*> m_Entities;
	IScene * m_Scene;

	Entity::ID m_LastID;
};


#endif