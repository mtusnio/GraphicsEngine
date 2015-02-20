#ifndef H_MODEL
#define H_MODEL

#include <vector>

#include "Material.h"

#include "../math/Vector.h"
#include "VertexBufferObject.h"

struct Model
{
	Model()
	{
		Material = nullptr;
		VBO = nullptr;
	}

	~Model()
	{
		if (Material)
			delete Material;

		if (VBO)
			delete VBO;
	}

	Material * Material;
	VertexBufferObject * VBO;

	std::vector<Vector> Vertices;
	std::vector<Vector> UVs;
	std::vector<Vector> Normals;

};


#endif