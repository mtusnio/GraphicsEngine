#ifndef H_IENTITYSYSTEM
#define H_IENTITYSYSTEM

#include <string>

#include "../entities/Entity.h"

class IEntitySystem
{
public:
	// Returns entity which identifies itself with this id
	// nullptr if no entity found
	virtual Entity * FindEntityByID(Entity::ID id) = 0;

	// Adds an entity to the current entitysystem, removes it from any other systems
	virtual void AddEntity(Entity * pEnt) = 0;
};


#endif