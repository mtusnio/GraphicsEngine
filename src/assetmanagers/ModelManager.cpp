#include "ModelManager.h"
#include "../tinyobjloader/tiny_obj_loader.h"
#include "../renderer/OpenGL/OpenGLVBO.h"

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

		// TODO: Optimize it later, i.e. by just reinterpret_casting the pointer to memory
		// to Vector class
		for (size_t i = 0; i < mesh.positions.size(); i += 3)
		{
			model->Vertices.push_back(Vector(mesh.positions[i], mesh.positions[i + 1], mesh.positions[i + 2]));
		}

		
	}
	

	// Uncomment to create VBOs
	// model->VBO = new OpenGLVBO();
	// model->VBO->Register(*model);

	return model;
}