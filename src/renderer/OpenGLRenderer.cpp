#include "OpenGLRenderer.h"

#include <GLFW\glfw3.h>
#include <cmath>

OpenGLRenderer::OpenGLRenderer(GLFWwindow * window)
{
	m_Window = window;
}
void OpenGLRenderer::RenderScene(IScene * scene)
{
	int width, height;

	glfwGetFramebufferSize(m_Window, &width, &height);
	float aspect = (float)width / (float)height;

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-aspect, aspect, -1.f, 1.f, 1.f, -1.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();

	glfwSwapBuffers(m_Window);
}