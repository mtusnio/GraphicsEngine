#ifndef H_IENTITYSYSTEM
#define H_IENTITYSYSTEM

#include <string>

#include "../entities/Entity.h"

class IScene;

class IEntitySystem
{
public:
	// Returns parent scene of this entity system
	virtual IScene * GetScene() const = 0;

	// Returns entity which identifies itself with this id
	// nullptr if no entity found
	virtual Entity * FindEntityByID(Entity::ID id) const = 0;

	// Adds an entity to the current entitysystem, removes it from any other systems.
	// Returns the object's assigned ID if it exists or if it's been added
	virtual Entity::ID AddEntity(Entity * pEnt) = 0;

	// Removes an entity from this system, if shouldDelete is set to false
	// it will not remove the object from memory, thus allowing it
	// to be attached to a different entity system
	virtual bool RemoveEntity(Entity * pEnt, bool shouldDelete = true) = 0;
};


#endif