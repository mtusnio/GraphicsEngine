#include "OpenGLTexture.h"
#include <SOIL.h>

OpenGLTexture::OpenGLTexture()
{
	TextureID = 0;
}

OpenGLTexture::~OpenGLTexture()
{
	if (!TextureID)
		glDeleteTextures(1, &TextureID);
}

std::string OpenGLTexture::Load(const std::string & path)
{
	_ASSERT(TextureID == 0);

	TextureID = SOIL_load_OGL_texture
		(
		path.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
		);

	if (TextureID == 0)
		return SOIL_last_result();

	return "";

	/*glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);*/
}