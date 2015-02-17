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
	void PrepareView();
	void InitializeProjectionMatrix(float fov, float aspect, float near, float far);

	void RenderObjects(IScene * scene);

	GLFWwindow * m_Window;
};


#endif