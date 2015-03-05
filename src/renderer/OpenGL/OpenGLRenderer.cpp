#include "OpenGLRenderer.h"

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Model.h"
#include "../../scene/IScene.h"
#include "../../entities/Entity.h"

#include "../../math/Vector.h"
#include "../../math/Angle.h"

#include "OpenGLTexture.h"

OpenGLRenderer::OpenGLRenderer(IGame & game)
{
	m_Game = &game;
	m_Program = glCreateProgram();

	auto & shaderMan = m_Game->GetShaderManager();

	m_VertexShader = std::static_pointer_cast<const OpenGLShader>(shaderMan.Cache("shaders/vertex.vert"));
	m_FragmentShader = std::static_pointer_cast<const OpenGLShader>(shaderMan.Cache("shaders/pixel.frag"));

	if (m_VertexShader && m_FragmentShader)
	{
		glAttachShader(m_Program, m_VertexShader->ShaderID);
		glAttachShader(m_Program, m_FragmentShader->ShaderID);
		glBindAttribLocation(m_Program, 0, "vertexPosition");
		glBindAttribLocation(m_Program, 1, "vertexColor");
	}
	else
		game.Log("Error loading shaders");

	glLinkProgram(m_Program);
	glUseProgram(m_Program);
}

OpenGLRenderer::~OpenGLRenderer()
{
	if (m_Program != 0)
		glDeleteProgram(m_Program);
}

void OpenGLRenderer::RenderScene(const IScene & scene, const Vector & cameraPosition, const Angle & cameraRotation) const
{
	int width, height;

	glfwGetFramebufferSize(m_Game->GetWindow(), &width, &height);
	float aspect = (float)width / (float)height;

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);

	Vector glPos = -ConvertToView(cameraPosition);
	Angle glRot = -ConvertToView(cameraRotation);

	glm::mat4 projection = glm::perspective(90.0f, aspect, 0.25f, 1000.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::rotate(view, glRot.x, glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, glRot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::rotate(view, glRot.z, glm::vec3(0.0f, 0.0f, 1.0f));
	view = glm::translate(view, glm::vec3(glPos.x, glPos.y, glPos.z));


	RenderObjects(view, projection, scene);

	glfwSwapBuffers(m_Game->GetWindow());
}

void OpenGLRenderer::RenderObjects(const glm::mat4 & view, const glm::mat4 & projection, const IScene & scene) const
{
	

	auto entities = scene.GetEntitySystem().GetEntities();

	glDisable(GL_TEXTURE_2D);
	for (auto pair : entities)
	{
		glPushMatrix();
		Entity * ent = pair.second;
		_ASSERT(ent != nullptr);

		Vector pos = ConvertToView(ent->GetPosition());

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, pos.z));
		const Model * pModel = pair.second->GetModel();

		_ASSERT(pModel != nullptr);

		glm::mat4 MVP = projection * view * model;
		GLuint MVPLocation = glGetUniformLocation(m_Program, "MVP");

		_ASSERT(MVPLocation != -1);

		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));
		for (const Model::Mesh * mesh : pModel->Meshes)
		{
			_ASSERT(mesh != nullptr && mesh->VAOs.size() > 0);

			if (mesh->VAOs.size() > 0)
			{
				// Render using VBO
				DrawMesh(*mesh);
			}
		
		}
		

		glPopMatrix();
		

	}
}

void OpenGLRenderer::DrawMesh(const Model::Mesh & mesh) const
{

}


Vector OpenGLRenderer::ConvertToView(const Vector & vec) const
{
	return Vector(-vec.y, vec.z, -vec.x);
}

Angle OpenGLRenderer::ConvertToView(const Angle & ang) const
{
	return Angle(ang.y, ang.z, -ang.x);
}