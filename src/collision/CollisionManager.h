#ifndef H_COLLISIONMANAGER
#define H_COLLISIONMANAGER

#include "ICollisionManager.h"

class IScene;
class Entity;

#include <vector>

class CollisionManager
{
public:
	CollisionManager(IScene & scene);
	virtual ~CollisionManager();

	virtual void Run();
	virtual bool CheckCollision(const Entity & ent1, const Entity & ent2) const;
private:

	IScene * m_Scene;
};

#endif