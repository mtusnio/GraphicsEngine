#ifndef H_IRENDERER
#define H_IRENDERER

class IScene;

class IRenderer
{
public:
	virtual void RenderScene(IScene * scene) = 0;

};
#endif