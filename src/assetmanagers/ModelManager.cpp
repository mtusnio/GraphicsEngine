#include "ModelManager.h"
#include "../tinyobjloader/tiny_obj_loader.h"
#include "../renderer/OpenGL/OpenGLVBO.h"
#include "../game/IGame.h"

Model * ModelManager::PerformCache(const std::string & path)
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string error = tinyobj::LoadObj(shapes, materials, path.c_str());

	_ASSERT(error == "");
	_ASSERT(shapes.size() != 0);

	if (error != "" || shapes.size() == 0)
		return nullptr;

	Model * model = new Model();


	for (size_t j = 0; j < shapes.size(); j++)
	{

		const tinyobj::mesh_t & mesh = shapes[j].mesh;

		_ASSERT(mesh.positions.size() % 3 == 0);
		_ASSERT(mesh.texcoords.size() % 2 == 0);
		_ASSERT(mesh.positions.size() / 3 == mesh.texcoords.size() / 2);
		if (mesh.positions.size() % 3 != 0 || mesh.texcoords.size() % 2 != 0)
		{
			m_Game.Log("Error at shape " + shapes[j].name);
			continue;
		}

		if (mesh.positions.size() / 3 != mesh.texcoords.size() / 2)
		{
			m_Game.Log("Shape " + shapes[j].name + " has a mismatch between tex coords and vertices");
			continue;
		}

		Model::Mesh * pModelMesh = new Model::Mesh();
		model->Meshes.push_back(pModelMesh);
		for (int indice : mesh.indices)
		{
			pModelMesh->Vertices.push_back(Vector(mesh.positions[indice * 3], mesh.positions[indice * 3 + 1], mesh.positions[indice * 3 + 2]));

			if (mesh.normals.size() > 0)
				pModelMesh->Normals.push_back(Vector(mesh.normals[indice * 3], mesh.normals[indice * 3 + 1], mesh.normals[indice * 3 + 2]));

			if (mesh.texcoords.size() > 0)
				pModelMesh->UVs.push_back(Vector(mesh.texcoords[indice * 2], mesh.texcoords[indice * 2 + 1], 0.0f));
		}

		
	}
	

	// Uncomment to create VBOs
	// model->VBO = new OpenGLVBO();
	// model->VBO->Register(*model);

	return model;
}