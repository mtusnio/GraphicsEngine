#ifndef H_ENTITY
#define H_ENTITY

#include <string>

class IEntitySystem;
class Entity
{
public:
	typedef unsigned long long int ID;
	const ID INVALID_ID = 0;

	Entity();
	virtual ~Entity();

	// If assigned, will return entity system we are attached to. Otherwise nullptr
	virtual IEntitySystem * GetEntitySystem() const { return m_EntitySystem;  }

	// Only changes the pointer to this object's entity system, use IEntitySystem
	// if you want to attach it to an entity system 
	virtual void SetEntitySystem(IEntitySystem * system) { m_EntitySystem = system; }

	// Changes the object's ID
	virtual void SetID(Entity::ID id) { m_EntityID = id;  }

private:
	// Unique ID
	ID m_EntityID;

	IEntitySystem * m_EntitySystem;
};


#endif