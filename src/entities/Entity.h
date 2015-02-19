#ifndef H_ENTITY
#define H_ENTITY

#include <string>

#include "../math/Vector.h"
#include "../math/Angle.h"

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
	IEntitySystem * GetEntitySystem() const { return m_EntitySystem;  }

	// Only changes the pointer to this object's entity system, use IEntitySystem
	// if you want to attach it to an entity system 
	void SetEntitySystem(IEntitySystem * system) { m_EntitySystem = system; }

	ID GetID() const { return m_EntityID;  }
	// Changes the object's Entity ID
	void SetID(Entity::ID id) { m_EntityID = id; }

	const Vector & GetPosition() const { return m_Position;  }
	void SetPosition(const Vector & pos) { m_Position = pos; }
	
	const Angle & GetRotation() const { return m_Rotation; }
	void SetRotation(Angle & rotation) { m_Rotation = rotation; }

	const Model * GetModel() const { return m_Model;  }
private:
	Vector m_Position;
	Angle m_Rotation;

	// Unique ID
	ID m_EntityID;

	Model * m_Model;
	IEntitySystem * m_EntitySystem;
};


#endif