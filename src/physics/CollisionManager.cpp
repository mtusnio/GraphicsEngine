#include "CollisionManager.h"
#include "../scene/IScene.h"

CollisionManager::CollisionManager(IScene & scene) :
m_Scene(&scene)
{

}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::Run()
{
	auto entities = m_Scene->GetEntitySystem().GetEntities();

	for (auto pair1 : entities)
	{
		Entity * main = pair1.second;
		for (auto pair2 : entities)
		{
			Entity * coll = pair2.second;

			if (main == coll)
				continue;

			if (coll->GetVelocity().LengthSqr() <= 0.25f)
				continue;

			if (coll->ShouldUsePhysics() && CheckCollision(*main, *coll))
				GenerateResponse(*main, *coll);
		}
	}
}

bool CollisionManager::CheckCollision(const Entity & ent1, const Entity & ent2) const
{
	Vector diff = ent2.GetPosition() - ent1.GetPosition();

	float radius1 = ent1.GetCollisionRadius() * ent1.GetCollisionRadius();
	float radius2 = ent2.GetCollisionRadius() * ent2.GetCollisionRadius();

	if (diff.LengthSqr() <= radius1 + radius2)
		return true;

	return false;
}

void CollisionManager::GenerateResponse(const Entity & entity, Entity & affected)
{
	affected.SetVelocity(Vector());
}