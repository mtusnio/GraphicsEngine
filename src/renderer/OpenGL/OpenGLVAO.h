#ifndef H_OpenGLVAO
#define H_OpenGLVAO


#include "../VertexArrayObject.h"
#include "OpenGLHeader.h"

class OpenGLVAO : public VertexArrayObject
{
public:
	OpenGLVAO();
	virtual ~OpenGLVAO();

	virtual void Register(const Model & model, unsigned int meshIndex, unsigned int materialIndex);

	GLuint ID;
	// VBO ids
	GLuint Vertices;
	GLuint Normals;
	GLuint Texcoords;
	GLuint Indice;
};

#endif