#ifndef H_SCENE
#define H_SCENE

#include "IScene.h"
#include "../entitysystem/EntitySystem.h"
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

	virtual void RegisterLight(const LightSource & light);
	virtual void UnregisterLight(const LightSource & light);
	virtual bool HasLightSource(const LightSource & light) const;
	virtual std::vector<const LightSource*> GetLightSources() const;

	// Returns parent game
	virtual IGame & GetGame() const { return *m_ParentGame; }

private:
	IGame * m_ParentGame;
	EntitySystem m_EntitySystem;

	std::vector<const LightSource*> m_LightSources;
};


#endif