#ifndef H_ISCENE
#define H_ISCENE

class IEntitySystem;
class IGame;

class IScene
{
public:
	virtual ~IScene() = 0;
	// Simulates all entities before frame rendering
	virtual void SimulatePreFrame() = 0;

	// Simulates all entites after frame rendering
	virtual void SimulatePostFrame() = 0;

	// Returns our entity system
	virtual IEntitySystem * GetEntitySystem() const = 0;

	// Returns parent game
	virtual IGame * GetGame() const = 0;
};


#endif