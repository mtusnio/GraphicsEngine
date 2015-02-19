#ifndef H_OPENGLRENDERER
#define H_OPENGLRENDERER

#include "IRenderer.h"

struct GLFWwindow;

struct Vector;
struct Angle;

class OpenGLRenderer : public IRenderer
{
public:
	OpenGLRenderer(GLFWwindow & window);

	virtual void RenderScene(const IScene & scene) const ;

private:
	void PrepareView() const;
	void InitializeProjectionMatrix(float fov, float aspect, float near, float far) const;

	void RenderObjects(const Vector & cameraPosition, const Angle & cameraRotation, const IScene & scene) const;

	GLFWwindow * m_Window;
};


#endif