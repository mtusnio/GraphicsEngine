#include "ModelManager.h"

#include <iterator>
#include <algorithm>

#include "../tinyobjloader/tiny_obj_loader.h"
#include "../renderer/OpenGL/OpenGLVAO.h"
#include "../game/IGame.h"

Model * ModelManager::PerformCache(const std::string & path) const
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string error = tinyobj::LoadObj(shapes, materials, path.c_str(), "materials/");

	if (error != "")
	{
		m_Game.Log(error);
		return nullptr;
	}
	
	_ASSERT(shapes.size() != 0);

	if (error != "" || shapes.size() == 0)
		return nullptr;

	Model * model = new Model();


	for (size_t j = 0; j < shapes.size(); j++)
	{
		tinyobj::mesh_t & mesh = shapes[j].mesh;

		_ASSERT(mesh.positions.size() % 3 == 0);
		_ASSERT(mesh.texcoords.size() % 2 == 0);
		//_ASSERT(mesh.positions.size() / 3 == mesh.texcoords.size() / 2);
		_ASSERT(mesh.material_ids.size() == mesh.indices.size()/3);

		if (mesh.positions.size() % 3 != 0 || mesh.texcoords.size() % 2 != 0)
		{
			m_Game.Log("Error at shape " + shapes[j].name);
			continue;
		}


		Model::Mesh * pModelMesh = LoadMesh(mesh, materials);
		_ASSERT(pModelMesh != nullptr);

		model->Meshes.push_back(pModelMesh);
	}
	

	// Uncomment to create VBOs
	// model->VBO = new OpenGLVAO();
	// model->VBO->Register(*model);

	return model;
}

#define FAST_LOAD

Model::Mesh * ModelManager::LoadMesh(tinyobj::mesh_t & mesh, const std::vector<tinyobj::material_t> & materials) const
{
	Model::Mesh * pModelMesh = new Model::Mesh();
	
#ifndef FAST_LOAD
	for (size_t i = 0; i < mesh.positions.size(); i += 3)
	{
		pModelMesh->Vertices.push_back(Vector(mesh.positions[i], mesh.positions[i + 1], mesh.positions[i + 2]));
	}
	for (size_t i = 0; i < mesh.normals.size(); i += 3)
	{
		pModelMesh->Normals.push_back(Vector(mesh.normals[i], mesh.normals[i + 1], mesh.normals[i + 2]));
	}
	for (size_t i = 0; i < mesh.texcoords.size(); i += 2)
	{
		pModelMesh->UVs.push_back({mesh.texcoords[i], mesh.texcoords[i+1]});
	}
	for (unsigned int indice : mesh.indices)
	{
		pModelMesh->Indices.push_back(indice);
	}
#else
	// Should be faster I guess?
	pModelMesh->Vertices = std::move(*reinterpret_cast<std::vector<Vector>*>(&mesh.positions));
	pModelMesh->Normals = std::move(*reinterpret_cast<std::vector<Vector>*>(&mesh.normals));
	pModelMesh->UVs = std::move(*reinterpret_cast<std::vector<Model::Mesh::UV>*>(&mesh.texcoords));
	pModelMesh->Indices = std::move(mesh.indices);
#endif

	int prev = mesh.material_ids[0];
	size_t indiceCount = pModelMesh->Indices.size();
	Model::Mesh::Range range = { 0, indiceCount };

	for (size_t i = 0; i < indiceCount; i++)
	{
		int indice = pModelMesh->Indices[i];
		int materialId = mesh.material_ids[i/3];
		if (prev != materialId)
		{
			range.second = i;
			if (prev != -1)
				pModelMesh->Materials[range] = LoadMaterial(materials[prev]);
			else
				pModelMesh->Materials[range] = nullptr;

			range.first = i;
			range.second = indiceCount;
			prev = materialId;
		}
	}

	if (range.first != range.second)
	{
		int materialId = mesh.material_ids[range.first/3];
		if (materialId != -1)
			pModelMesh->Materials[range] = LoadMaterial(materials[materialId]);
		else
			pModelMesh->Materials[range] = nullptr;
	}

#ifdef _DEBUG
	// Make sure our ranges cover everything properly
	int sum = 0;
	for (auto mat : pModelMesh->Materials)
	{
		sum += mat.first.second - mat.first.first;
	}

	_ASSERT(sum == indiceCount);

#endif

	return pModelMesh;
}

Material * ModelManager::LoadMaterial(const tinyobj::material_t & tinyMat) const
{
	Material * material = new Material();
	std::copy(std::begin(tinyMat.ambient), std::end(tinyMat.ambient), std::begin(material->Ambient));
	std::copy(std::begin(tinyMat.diffuse), std::end(tinyMat.diffuse), std::begin(material->Diffuse));
	std::copy(std::begin(tinyMat.specular), std::end(tinyMat.specular), std::begin(material->Specular));
	std::copy(std::begin(tinyMat.transmittance), std::end(tinyMat.transmittance), std::begin(material->Transmittance));
	std::copy(std::begin(tinyMat.emission), std::end(tinyMat.emission), std::begin(material->Emission));
	material->Shininess = tinyMat.shininess;
	material->IndexOfRefraction = tinyMat.ior;
	material->Opaque = tinyMat.dissolve;

	AssetManager<Texture> & manager = m_Game.GetTextureManager();

	if (tinyMat.ambient_texname != "")
		material->AmbientTex = manager.Cache("textures/" + tinyMat.ambient_texname);
	if (tinyMat.diffuse_texname != "")
		material->DiffuseTex = manager.Cache("textures/" + tinyMat.diffuse_texname);
	if (tinyMat.specular_texname != "")
		material->SpecularTex = manager.Cache("textures/" + tinyMat.specular_texname);
	if (tinyMat.normal_texname != "")
		material->NormalTex = manager.Cache("textures/" + tinyMat.normal_texname);

	material->Parameters = std::move(tinyMat.unknown_parameter);

	return material;
}