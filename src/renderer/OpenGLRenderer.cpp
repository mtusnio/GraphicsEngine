#include "OpenGLRenderer.h"

#include <GLFW\glfw3.h>
#include <cmath>

OpenGLRenderer::OpenGLRenderer(GLFWwindow & window)
{
	m_Window = &window;
}

void OpenGLRenderer::PrepareView()
{
	int width, height;

	glfwGetFramebufferSize(m_Window, &width, &height);
	float aspect = (float)width / (float)height;

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	InitializeProjectionMatrix(90.0f, aspect, 10.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OpenGLRenderer::RenderScene(const IScene & scene)
{
	PrepareView();

	RenderObjects(scene);

	glfwSwapBuffers(m_Window);
}

void OpenGLRenderer::RenderObjects(const IScene & scene)
{

}

void OpenGLRenderer::InitializeProjectionMatrix(float fov, float aspect, float near, float far)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float e = 1.f / tanf(fov / 2.0f);
	float width = near * e;
	glFrustum(-width, width, -aspect * width, aspect * width, near, far);
}