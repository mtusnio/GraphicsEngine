#ifndef H_OpenGLVAO
#define H_OpenGLVAO


#include "../VertexArrayObject.h"
#include "OpenGLHeader.h"

class OpenGLVAO : public VertexArrayObject
{
public:
	OpenGLVAO();
	virtual ~OpenGLVAO();


	virtual void Register(Model & model, unsigned int meshIndex, unsigned int materialIndex);
	virtual void DestroySharedData();

	GLuint ID;
	// VBO ids
	GLuint Vertices;
	GLuint Normals;
	GLuint Texcoords;
	GLuint Indice;
};

#endif