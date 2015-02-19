#ifndef H_SCENE
#define H_SCENE

#include "IScene.h"
#include "../entitysystem/EntitySystem.h"
class Scene : public IScene
{
public:
	Scene(IGame * game);
	virtual ~Scene();

	// Simulates all entities before frame rendering
	virtual void SimulatePreFrame();

	// Simulates all entites after frame rendering
	virtual void SimulatePostFrame();

	// Returns our entity system
	virtual IEntitySystem * GetEntitySystem()  { return &m_EntitySystem;  }

	// Returns parent game
	virtual IGame * GetGame() const { return m_ParentGame; }

private:
	IGame * m_ParentGame;
	EntitySystem m_EntitySystem;
};


#endif