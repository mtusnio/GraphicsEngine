#ifndef H_MODEL
#define H_MODEL

#include <vector>
#include <memory>

#include "Material.h"

#include "../math/Vector.h"
#include "../math/Box.h"
#include "VertexArrayObject.h"

struct Model
{
	struct Mesh
	{
		typedef std::pair<float, float> UV;
		typedef std::pair<unsigned int, unsigned int> Range;

		~Mesh()
		{
			if (VAOs.size() > 0)
				VAOs[0]->DestroySharedData();

			for (VertexArrayObject * vao : VAOs)
			{
				delete vao;
			}

			for (auto mat : Materials)
			{
				delete mat.second;
			}
		}

		std::vector<Vector> Vertices;
		std::vector<UV> UVs;
		std::vector<Vector> Normals;
		std::vector<unsigned int> Indices;

		// Stores materials per indice
		std::vector<std::pair<Range, Material*>> Materials;
		std::vector<VertexArrayObject*> VAOs;

	};

	~Model()
	{
		for (Mesh * mesh : Meshes)
			delete mesh;
	}

	std::vector<Mesh*> Meshes;
	float CollisionSphere;
	Box BoundingBox;
};





#endif