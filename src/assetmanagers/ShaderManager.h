#ifndef H_SHADERMANAGER
#define H_SHADERMANAGER

#include "AssetManager.h"
#include "../renderer/Shader.h"

class ShaderManager : AssetManager<Shader>
{
public:
	ShaderManager(IGame & game) : AssetManager<Shader>(game) { };
	virtual ~ShaderManager() { };

private:
	virtual Shader * PerformCache(const std::string & path) const;
};


#endif