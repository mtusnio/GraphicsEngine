#include "TextureManager.h"

#include <string>

#include "../renderer/OpenGL/OpenGLTexture.h"

Texture * TextureManager::PerformCache(const std::string & path) const
{
	OpenGLTexture * tex = new OpenGLTexture();

	tex->Load(path);

	if (tex->TextureID == 0)
	{
		delete tex;
		return nullptr;
	}
	return tex;
}