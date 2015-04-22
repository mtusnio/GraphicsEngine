#ifndef H_IENTITYSYSTEM
#define H_IENTITYSYSTEM

#include <string>
#include <unordered_map>

#include "../entities/Entity.h"

class IScene;

class IEntitySystem
{
public:
	virtual ~IEntitySystem() { };

	// Returns parent scene of this entity system
	virtual IScene * GetScene() const = 0;

	// Sets current parent scene
	virtual void SetScene(IScene * scene) = 0;

	// Returns entity which identifies itself with this id
	// nullptr if no entity found
	virtual Entity * FindEntityByID(Entity::ID id) = 0;

	// Creates a new entity in this entity system
	virtual Entity * CreateEntity() = 0;

	// Removes an entity from this system and deletes it
	virtual bool RemoveEntity(Entity & pEnt) = 0;

	// Creates a vector with all of our entities. Expensive if called frequently,
	// use other functions unless aboslutely needed
	virtual const std::unordered_map<Entity::ID, Entity> & GetEntities() const = 0;
};


#endif