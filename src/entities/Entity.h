#ifndef H_ENTITY
#define H_ENTITY

#include <string>

class IEntitySystem;
struct Model;

class Entity
{
public:
	typedef unsigned long long int ID;
	static const ID INVALID_ID = 0;

	Entity();
	virtual ~Entity();

	virtual void RunPreFrame() { }
	virtual void RunPostFrame() { }

	// If assigned, will return entity system we are attached to. Otherwise nullptr
	virtual IEntitySystem * GetEntitySystem() const { return m_EntitySystem;  }

	// Only changes the pointer to this object's entity system, use IEntitySystem
	// if you want to attach it to an entity system 
	virtual void SetEntitySystem(IEntitySystem * system) { m_EntitySystem = system; }

	virtual ID GetID() const { return m_EntityID;  }
	// Changes the object's Entity ID
	virtual void SetID(Entity::ID id) { m_EntityID = id;  }


	virtual const Model * GetModel() const { return m_Model;  }
private:
	// Unique ID
	ID m_EntityID;

	Model * m_Model;
	IEntitySystem * m_EntitySystem;
};


#endif