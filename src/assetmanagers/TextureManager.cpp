#include "TextureManager.h"

#include <string>

#include "../renderer/OpenGL/OpenGLTexture.h"

Texture * TextureManager::PerformCache(const std::string & path) const
{
	Texture * tex = new OpenGLTexture();

	tex->Load(path);

	return tex;
}