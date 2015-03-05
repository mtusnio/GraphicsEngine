#ifndef H_VertexArrayObject
#define H_VertexArrayObject

struct Model;

class VertexArrayObject
{
public:
	virtual ~VertexArrayObject() { }

	virtual void Register(Model & model, unsigned int meshIndex, unsigned int materialIndex) = 0;
	// If you have a collection of VAOs registered to the same model call this on the FIRST vbo to remove
	// all shared data, then proceed to delete them as usual
	virtual void DestroySharedData() = 0;
};

#endif