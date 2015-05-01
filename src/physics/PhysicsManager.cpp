#include "PhysicsManager.h"
#include "../scene/IScene.h"

PhysicsManager::PhysicsManager(IScene & scene) :
m_Scene(&scene)
{

}

PhysicsManager::~PhysicsManager()
{

}

void PhysicsManager::Run()
{
	auto entities = m_Scene->GetEntitySystem().GetEntities();

	Time time = m_Scene->GetGame().GetTime();

	for (auto pair : entities)
	{
		Entity * ent = pair.second;

		if (!ent->ShouldUsePhysics())
			continue;

		ent->SetPosition(ent->GetPosition() + ent->GetVelocity() * time.Delta);

		ent->AddVelocity(Vector(0, 0, -3) * time.Delta);
	}

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

bool PhysicsManager::CheckCollision(const Entity & ent1, const Entity & ent2) const
{
	Vector diff = ent2.GetPosition() - ent1.GetPosition();

	float radius1 = ent1.GetCollisionRadius() * ent1.GetCollisionRadius();
	float radius2 = ent2.GetCollisionRadius() * ent2.GetCollisionRadius();

	if (diff.LengthSqr() <= radius1 + radius2)
		return true;

	return false;
}

void PhysicsManager::GenerateResponse(const Entity & entity, Entity & affected)
{
	affected.SetVelocity(Vector());
}