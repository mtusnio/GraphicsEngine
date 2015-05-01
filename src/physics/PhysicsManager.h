#ifndef H_COLLISIONMANAGER
#define H_COLLISIONMANAGER

#include "IPhysicsManager.h"

class IScene;
class Entity;

#include <vector>

class PhysicsManager
{
public:
	PhysicsManager(IScene & scene);
	virtual ~PhysicsManager();

	virtual void Run();
	virtual bool CheckCollision(const Entity & ent1, const Entity & ent2) const;
private:
	virtual void GenerateResponse(const Entity & entity, Entity & affected);



	IScene * m_Scene;
};

#endif