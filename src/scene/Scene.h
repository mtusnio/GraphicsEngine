#ifndef H_SCENE
#define H_SCENE

#include <unordered_map>

#include "IScene.h"
#include "../entitysystem/EntitySystem.h"

#include "../physics/CollisionManager.h"

class Scene : public IScene
{
public:
	Scene(IGame & game);
	virtual ~Scene();

	// Simulates all entities before frame rendering
	virtual void SimulatePreFrame();

	// Simulates all entites after frame rendering
	virtual void SimulatePostFrame();

	// Returns our entity system
	virtual IEntitySystem & GetEntitySystem()  { return m_EntitySystem;  }
	virtual const IEntitySystem & GetEntitySystem() const { return m_EntitySystem; }

	virtual void RegisterLight(const LightSource & light, LightSource::Type type);
	virtual void UnregisterLight(const LightSource & light);
	virtual bool HasLightSource(const LightSource & light) const;
	virtual std::vector<const LightSource*> GetLightSources(LightSource::Type type) const;

	// Returns parent game
	virtual IGame & GetGame() const { return *m_ParentGame; }

private:
	IGame * m_ParentGame;
	EntitySystem m_EntitySystem;
	CollisionManager m_CollisionManager;

	std::unordered_map<LightSource::Type, std::vector<const LightSource*> > m_LightSources;
};


#endif