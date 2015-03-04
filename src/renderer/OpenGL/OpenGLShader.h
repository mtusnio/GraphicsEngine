#ifndef H_OPENGLSHADER
#define H_OPENGLSHADER

#include "../Shader.h"

struct OpenGLShader : public Shader
{
	OpenGLShader();
	virtual ~OpenGLShader();

	virtual std::string Load(const std::string & path);
};

#endif