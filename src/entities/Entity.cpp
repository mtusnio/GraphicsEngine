#include "Entity.h"
#include "../renderer/Model.h"


Entity::Entity()
{
	m_EntitySystem = nullptr;
	m_EntityID = INVALID_ID;
}

Entity::~Entity()
{

}

void Entity::SetModel(const std::shared_ptr<const Model> & model)
{
	m_Model = model;

	CalculateCollision();
}

void Entity::CalculateCollision()
{
	if (m_Model.get() == nullptr)
		return;

	float maxDistanceSqr = 0.0f;

	auto maxFunction = [&](float & variable, float & vectorVar)
	{
		if (vectorVar > variable)
		{
			variable = vectorVar;
			return true;
		}
		return false;
	};
	auto minFunction = [](float & variable, float & vectorVar)
	{
		if (vectorVar < variable)
			variable = vectorVar;
	};


	auto meshes = m_Model.get()->Meshes;

	float max[3] = { 0.0f, 0.0f, 0.0f };
	float min[3] = { 0.0f, 0.0f, 0.0f };

	for (Model::Mesh * mesh : meshes)
	{
		for (auto vertex : mesh->Vertices)
		{
			float dist = vertex.LengthSqr();

			if (dist > maxDistanceSqr)
				maxDistanceSqr = dist;
			
			if (!maxFunction(max[0], vertex.x))
				minFunction(min[0], vertex.x);
			if (!maxFunction(max[1], vertex.y))
				minFunction(min[1], vertex.y);
			if (!maxFunction(max[2], vertex.z))
				minFunction(min[2], vertex.z);
		}
	}

	m_Sphere = std::sqrt(maxDistanceSqr);

	m_BoundingBox = Box(Vector(min[0], min[1], min[2]), Vector(min[0], max[1], min[2]), Vector(max[0], max[1], min[2]), Vector(max[0], min[1], min[2]), 
					Vector(min[0], min[1], max[2]), Vector(min[0], max[1], max[2]), Vector(max[0], max[1], max[2]), Vector(max[0], min[1], max[2]));
}