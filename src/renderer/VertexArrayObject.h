#ifndef H_VertexArrayObject
#define H_VertexArrayObject

struct Model;

class VertexArrayObject
{
public:
	virtual ~VertexArrayObject() { }

	virtual void Register(const Model & model, unsigned int meshIndex, unsigned int materialIndex) = 0;
};

#endif