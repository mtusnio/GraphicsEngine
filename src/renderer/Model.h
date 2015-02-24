#ifndef H_MODEL
#define H_MODEL

#include <vector>

#include "Material.h"

#include "../math/Vector.h"
#include "VertexBufferObject.h"



struct Model
{
	struct Mesh
	{
		Mesh()
		{
			Material = nullptr;
			VBO = nullptr;
		}

		~Mesh()
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

	~Model()
	{
		for (Mesh * mesh : Meshes)
			delete mesh;
	}
	std::vector<Mesh*> Meshes;
};





#endif