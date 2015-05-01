#ifndef H_MODELMANAGER
#define H_MODELMANAGER

#include "AssetManager.h"
#include "../renderer/Model.h"

#include "../tinyobjloader/tiny_obj_loader.h"

class ModelManager : public AssetManager<Model>
{
public:
	ModelManager(IGame & game) : AssetManager<Model>(game) { }
private:
	virtual Model * PerformCache(const std::string & path);

	Model::Mesh * LoadMesh(tinyobj::mesh_t & mesh, const std::vector<tinyobj::material_t> & materials) const;
	Material * LoadMaterial(const tinyobj::material_t & tinyMat) const;

	void CalculateCollisions(Model & model) const;
};

#endif