#ifndef H_OCTREE
#define H_OCTREE

#include <vector>

#include "../entitysystem/Handle.h"

class Octree
{
	static const int MAX_LEVEL = 5;

	// Accepts a parameter which specifies for how many
	// objects should the memory be reserved
	Octree(int memReserve = 20);
	virtual ~Octree();

private:
	int m_Level;

	std::vector<Handle<Entity>*> m_Entities;
	int m_EntityCount;
};




#endif