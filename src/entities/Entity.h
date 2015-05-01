#ifndef H_ENTITY
#define H_ENTITY

#include <string>
#include <memory>

#include "../math/Vector.h"
#include "../math/Angle.h"
#include "../math/Box.h"

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

	const Model * GetModel() const { return m_Model.get();  }
	void SetModel(const std::shared_ptr<const Model> & model) { m_Model = model; }

	void AddVelocity(const Vector & vel) { m_Velocity += vel;  }
	void SetVelocity(const Vector & vel) { m_Velocity = vel; }
	const Vector & GetVelocity() const { return m_Velocity;  }

	void SetPhysicsEnabled(bool physics) { m_Physics = physics; }
	bool ShouldUsePhysics() const { return m_Physics;  }
private:
	Vector m_Velocity;
	Vector m_Position;
	Angle m_Rotation;

	bool m_Physics;

	// Unique ID
	ID m_EntityID;

	std::shared_ptr<const Model> m_Model;
	IEntitySystem * m_EntitySystem;
};


#endif