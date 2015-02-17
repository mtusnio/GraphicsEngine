#ifndef H_OPENGLRENDERER
#define H_OPENGLRENDERER

#include "IRenderer.h"

struct GLFWwindow;
class OpenGLRenderer : public IRenderer
{
public:
	OpenGLRenderer(GLFWwindow * window);

	virtual void RenderScene(IScene * scene);

private:
	GLFWwindow * m_Window;
};


#endif