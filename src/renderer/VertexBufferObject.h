#ifndef H_VERTEXBUFFEROBJECT
#define H_VERTEXBUFFEROBJECT

struct Model;

class VertexBufferObject
{
public:
	virtual void Register(const Model & model) = 0;
	virtual void Destroy() = 0;
};

#endif