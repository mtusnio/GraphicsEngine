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

		if (mesh.positions.size() % 3 != 0)
		{
			m_Game.Log("Error at mesh " + std::to_string(j) + " . Size: " + std::to_string(mesh.positions.size()) );
			continue;
		}

		for (int i : mesh.indices)
		{
			model->Vertices.push_back(Vector(mesh.positions[i * 3], mesh.positions[i * 3 + 1], mesh.positions[i * 3+ 2]));
		}

		
	}
	

	// Uncomment to create VBOs
	// model->VBO = new OpenGLVBO();
	// model->VBO->Register(*model);

	return model;
}