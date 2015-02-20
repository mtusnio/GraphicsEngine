#ifndef H_OPENGLVBO
#define H_OPENGLVBO

#include "../VertexBufferObject.h"

class OpenGLVBO : public VertexBufferObject
{
public:
	virtual void Register(const Model & model);
	virtual void Destroy();
};

#endif