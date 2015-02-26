#include "ModelManager.h"

#include <iterator>
#include <algorithm>

#include "../tinyobjloader/tiny_obj_loader.h"
#include "../renderer/OpenGL/OpenGLVBO.h"
#include "../game/IGame.h"

Model * ModelManager::PerformCache(const std::string & path) const
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string error = tinyobj::LoadObj(shapes, materials, path.c_str(), "materials/");

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
				pModelMesh->UVs.push_back(Model::Mesh::UV(mesh.texcoords[indice * 2], mesh.texcoords[indice * 2 + 1]));
		}

	
		if (mesh.material_ids.size() > 0)
		{
			tinyobj::material_t tinyMat = materials[mesh.material_ids[0]];
			

			Material * material = new Material();
			pModelMesh->Material = material;
			std::copy(std::begin(tinyMat.ambient), std::end(tinyMat.ambient), std::begin(material->Ambient));
			std::copy(std::begin(tinyMat.diffuse), std::end(tinyMat.diffuse), std::begin(material->Diffuse));
			std::copy(std::begin(tinyMat.specular), std::end(tinyMat.specular), std::begin(material->Specular));
			std::copy(std::begin(tinyMat.transmittance), std::end(tinyMat.transmittance), std::begin(material->Transmittance));
			std::copy(std::begin(tinyMat.emission), std::end(tinyMat.emission), std::begin(material->Emission));
			material->Shininess = tinyMat.shininess;
			material->IndexOfRefraction = tinyMat.ior;
			material->Opaque = tinyMat.dissolve;

			AssetManager<Texture> & manager = m_Game.GetTextureManager();

			material->AmbientTex = manager.Cache("textures/" + tinyMat.ambient_texname);
			material->DiffuseTex = manager.Cache("textures/" + tinyMat.diffuse_texname);
			material->SpecularTex = manager.Cache("textures/" + tinyMat.specular_texname);
			material->NormalTex = manager.Cache("textures/" + tinyMat.normal_texname);
			material->Parameters = std::move(tinyMat.unknown_parameter);
		}
		
	}
	

	// Uncomment to create VBOs
	// model->VBO = new OpenGLVBO();
	// model->VBO->Register(*model);

	return model;
}