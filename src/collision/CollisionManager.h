#ifndef H_COLLISIONMANAGER
#define H_COLLISIONMANAGER

#include "ICollisionManager.h"

class IScene;

class CollisionManager
{
public:
	CollisionManager(IScene & scene);
	virtual ~CollisionManager();

	virtual void Run();
};

#endif