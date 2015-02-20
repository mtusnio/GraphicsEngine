#include "ModelManager.h"
#include "../tinyobjloader/tiny_obj_loader.h"
#include "../renderer/OpenGL/OpenGLVBO.h"
Model * ModelManager::PerformCache(const std::string & path)
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string error = tinyobj::LoadObj(shapes, materials, path.c_str());

	_ASSERT(error == "");
	if (error != "" || shapes.size() == 0)
		return nullptr;

	Model * model = new Model();

	tinyobj::mesh_t & mesh = shapes[0].mesh;

	// TODO: Optimize it later, i.e. by just reinterpret_casting the pointer to memory
	// to Vector class
	for (unsigned int i = 2; i < mesh.positions.size(); i += 3)
	{
		model->Vertices.push_back(Vector(mesh.positions[i - 2], mesh.positions[i - 1], mesh.positions[i]));
	}

	for (unsigned int i = 2; i < mesh.normals.size(); i += 3)
	{
		model->Normals.push_back(Vector(mesh.normals[i - 2], mesh.normals[i - 1], mesh.normals[i]));
	}

	// Uncomment to create VBOs
	// model->VBO = new OpenGLVBO();
	// model->VBO->Register(*model);

	return model;
}