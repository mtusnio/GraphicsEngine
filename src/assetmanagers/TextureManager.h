#ifndef H_MATERIALMANAGER
#define H_MATERIALMANAGER

#include "AssetManager.h"
#include "../renderer/Material.h"

class TextureManager : AssetManager<Texture>
{
public:
	TextureManager(IGame & game) : AssetManager<Texture>(game) { };
	virtual ~TextureManager() { };

private:
	virtual Texture * PerformCache(const std::string & path) const;
};

#endif