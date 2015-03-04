#ifndef H_ISCENE
#define H_ISCENE

#include "../entitysystem/IEntitySystem.h"
#include "../game/IGame.h"

class IScene
{
public:
	virtual ~IScene() { };
	// Simulates all entities before frame rendering
	virtual void SimulatePreFrame() = 0;

	// Simulates all entites after frame rendering
	virtual void SimulatePostFrame() = 0;

	// Returns our entity system
	virtual IEntitySystem & GetEntitySystem() = 0;
	virtual const IEntitySystem & GetEntitySystem() const = 0;

	// Returns parent game
	virtual IGame & GetGame() const = 0;
};


#endif