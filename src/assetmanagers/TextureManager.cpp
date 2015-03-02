#include "TextureManager.h"

#include <string>
#include <SOIL.h>

#include "../renderer/OpenGL/OpenGLTexture.h"
#include "../game/IGame.h"

Texture * TextureManager::PerformCache(const std::string & path) const
{
	OpenGLTexture * tex = new OpenGLTexture();

	tex->Load(path);

	if (tex->TextureID == 0)
	{
		delete tex;
		throw AssetError(std::string(SOIL_last_result()));
	}
	return tex;
}