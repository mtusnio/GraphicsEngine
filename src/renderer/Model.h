#ifndef H_MODEL
#define H_MODEL

#include <vector>
#include <memory>

#include "Material.h"

#include "../math/Vector.h"
#include "VertexBufferObject.h"



struct Model
{
	struct Mesh
	{
		typedef std::pair<float, float> UV;

		Mesh()
		{
			VBO = nullptr;
			Material = nullptr;
		}

		~Mesh()
		{

			if (VBO)
				delete VBO;

			if (Material)
				delete Material;
		}

		Material * Material;
		VertexBufferObject * VBO;

		std::vector<Vector> Vertices;
		std::vector<UV> UVs;
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