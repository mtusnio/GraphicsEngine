#ifndef H_MODEL
#define H_MODEL

#include <vector>

#include "Material.h"

#include "../math/Vector.h"


struct Model
{
	Material * m_Material;

	std::vector<Vector> Vertices;
};


#endif