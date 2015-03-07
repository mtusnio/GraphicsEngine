#ifndef H_ISCENE
#define H_ISCENE

#include "../entitysystem/IEntitySystem.h"
#include "../game/IGame.h"
#include "LightSource.h"

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

	// Registers our light source in the scene. The object containing the LightSource
	// structure is responsible for handling its lifetime by calling the Unregister method
	virtual void RegisterLight(const LightSource & light, LightSource::Type type) = 0;

	// Call before the light is deleted or when you no longer want to use it in the scene
	virtual void UnregisterLight(const LightSource & light) = 0;

	// Returns true if this light source has already been registered
	virtual bool HasLightSource(const LightSource & light) const = 0;

	// Returns all registered LightSources
	virtual std::vector<const LightSource*> GetLightSources(LightSource::Type type) const = 0;

	// Returns parent game
	virtual IGame & GetGame() const = 0;
};


#endif