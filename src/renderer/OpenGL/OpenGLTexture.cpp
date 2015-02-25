#include "OpenGLTexture.h"
#include <SOIL.h>

OpenGLTexture::OpenGLTexture()
{
	TextureID = 0;
}

OpenGLTexture::~OpenGLTexture()
{

}

void OpenGLTexture::Load(const std::string & path)
{
	_ASSERT(TextureID == 0);

	TextureID = SOIL_load_OGL_texture
		(
		path.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
}