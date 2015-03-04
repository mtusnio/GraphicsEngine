#ifndef H_OPENGLTEXTURE
#define H_OPENGLTEXTURE

#include "../Texture.h"

#include <glfw/glfw3.h>

struct OpenGLTexture : public Texture
{
	OpenGLTexture();
	virtual ~OpenGLTexture();

	virtual std::string Load(const std::string & path);

	GLuint TextureID;
};

#endif