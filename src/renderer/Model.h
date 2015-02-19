#ifndef H_MODEL
#define H_MODEL

#include <vector>

#include "Material.h"

#include "../math/Vector.h"
#include "VertexBufferObject.h"

struct Model
{
	Material * m_Material;

	VertexBufferObject m_VBO;
};


#endif