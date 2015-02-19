#ifndef H_IRENDERER
#define H_IRENDERER

class IScene;

class IRenderer
{
public:
	virtual void RenderScene(const IScene & scene) const = 0;

};
#endif