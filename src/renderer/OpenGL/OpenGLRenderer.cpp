#include "OpenGLRenderer.h"

#include <GLFW\glfw3.h>
#include <cmath>

#include "../Model.h"
#include "../../scene/IScene.h"
#include "../../entities/Entity.h"

#include "../../math/Vector.h"
#include "../../math/Angle.h"

OpenGLRenderer::OpenGLRenderer(GLFWwindow & window)
{
	m_Window = &window;
}

void OpenGLRenderer::PrepareView() const
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

void OpenGLRenderer::RenderScene(const IScene & scene, const Vector & cameraPosition, const Angle & cameraRotation) const
{
	PrepareView();

	TranslateCurrentMatrix(-cameraPosition);

	RenderObjects(cameraPosition, cameraRotation, scene);

	glfwSwapBuffers(m_Window);
}

void OpenGLRenderer::RenderObjects(const Vector & cameraPosition, const Angle & cameraRotation, const IScene & scene) const
{
	auto entities = scene.GetEntitySystem().GetEntities();

	for (auto pair : entities)
	{
		glPushMatrix();
		Entity * ent = pair.second;
		_ASSERT(ent != nullptr);

		Vector diff = ent->GetPosition() - cameraPosition;

		TranslateCurrentMatrix(diff);
		
		const Model * pModel = pair.second->GetModel();
		if (!pModel)
			continue;



		glPopMatrix();
		

	}
}

void OpenGLRenderer::InitializeProjectionMatrix(float fov, float aspect, float near, float far) const
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float e = 1.f / tanf(fov / 2.0f);
	float width = near * e;
	glFrustum(-width, width, -aspect * width, aspect * width, near, far);
}

void OpenGLRenderer::TranslateCurrentMatrix(const Vector & translation) const
{
	glTranslatef(translation.y, translation.z, -translation.x);
}

void OpenGLRenderer::RotateCurrentMatrix(const Angle & rotation) const
{

}