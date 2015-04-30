#include "Octree.h"

Octree::Octree(int memReserve)
{
	m_Entities.resize(memReserve);
	m_EntityCount = 0;
}

Octree::~Octree()
{
	for (int i = 0; i < m_EntityCount; i++)
	{
		delete m_Entities[i];
	}
}