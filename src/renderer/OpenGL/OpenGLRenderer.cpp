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
#include "OpenGLVAO.h"

#include "../../scene/LightSource.h"

OpenGLRenderer::OpenGLRenderer(IGame & game)
{
	m_Game = &game;
	
	InitializeShaders();
	InitializeSampler();
	InitializeBaseTexture();

}

OpenGLRenderer::~OpenGLRenderer()
{
	if (m_Program != 0)
		glDeleteProgram(m_Program);

	if (m_LinearSampler != 0)
		glDeleteSamplers(1, &m_LinearSampler);

	if (m_BaseTexture != 0)
		glDeleteTextures(1, &m_BaseTexture);
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
	view = glm::rotate(view, glm::radians(glRot.x), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, glm::radians(glRot.y), glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::rotate(view, glm::radians(glRot.z), glm::vec3(0.0f, 0.0f, 1.0f));
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
		Angle ang = ConvertToView(ent->GetRotation());
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, pos.z));
		model = glm::rotate(model, glm::radians(ang.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(ang.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(ang.z), glm::vec3(0.0f, 0.0f, 1.0f));

		const Model * pModel = pair.second->GetModel();

		_ASSERT(pModel != nullptr);

		glm::mat4 MVP = projection * view * model;
		GLuint MVPLocation = glGetUniformLocation(m_Program, "MVP");

		_ASSERT(MVPLocation != -1);

		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));
		for (const Model::Mesh * mesh : pModel->Meshes)
		{
			_ASSERT(mesh != nullptr && mesh->VAOs.size() > 0);

			BindLightSources(scene);
			DrawMesh(*mesh);
		}

	}
}

void OpenGLRenderer::DrawMesh(const Model::Mesh & mesh) const
{
	
	for (size_t i = 0; i < mesh.VAOs.size(); i++)
	{
		OpenGLVAO * vao = static_cast<OpenGLVAO*>(mesh.VAOs[i]);
		_ASSERT(vao != nullptr && vao->ID != 0);

		auto pair = mesh.Materials[i];

		BindTextures(pair.second);

		glBindVertexArray(vao->ID);
		glDrawElements(GL_TRIANGLES, vao->Size, GL_UNSIGNED_INT, (void*)0);
		glBindVertexArray(0);
	}
}

void OpenGLRenderer::BindLightSources(const IScene & scene) const
{
	auto sources = scene.GetLightSources(LightSource::SPOT);

	size_t lightCount = (int)fmin(8, sources.size());

	glUniform1i(glGetUniformLocation(m_Program, "SpotlightCount"), lightCount);

	for (size_t i = 0; i < lightCount; i++)
	{
		const SpotLightSource * light = static_cast<const SpotLightSource*>(sources[i]);

		_ASSERT(light != nullptr);

		std::string lightName = "Spotlights[" + std::to_string(i) + "]";
		Vector dir = ConvertToView(light->Rotation.ToDirection());
		glUniform3f(glGetUniformLocation(m_Program, (lightName + ".Direction").c_str()), dir.x, dir.y, dir.z);
		Vector lightPosition = ConvertToView(light->Position);
		glUniform3f(glGetUniformLocation(m_Program, (lightName + ".Position").c_str()), lightPosition.x, lightPosition.y, lightPosition.z);
		glUniform3f(glGetUniformLocation(m_Program, (lightName + ".Color").c_str()), light->Color[0], light->Color[1], light->Color[2]);
		glUniform1f(glGetUniformLocation(m_Program, (lightName + ".Exponent").c_str()), light->Exponent);
		glUniform1f(glGetUniformLocation(m_Program, (lightName + ".Linear").c_str()), light->Attenuation.Linear);
		glUniform1f(glGetUniformLocation(m_Program, (lightName + ".Constant").c_str()), light->Attenuation.Constant);
		glUniform1f(glGetUniformLocation(m_Program, (lightName + ".Quadratic").c_str()), light->Attenuation.Quadratic);
	}
}

void OpenGLRenderer::BindTextures(const Material * mat) const
{
	glUniform1i(glGetUniformLocation(m_Program, "diffuseTexture"), 0);

	glActiveTexture(GL_TEXTURE0);
	if (!mat || mat->DiffuseTex.get() == nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, m_BaseTexture);
		glUniform3f(glGetUniformLocation(m_Program, "ambientIntensity"), 0.0f, 0.0f, 0.0f);
	}
	else
	{
		const OpenGLTexture * tex = static_cast<const OpenGLTexture*>(mat->DiffuseTex.get());
		glBindTexture(GL_TEXTURE_2D, tex->TextureID);
		glUniform3fv(glGetUniformLocation(m_Program, "ambientIntensity"), 1, mat->Ambient);
	}
	glBindSampler(0, m_LinearSampler);
	
}

void OpenGLRenderer::InitializeShaders()
{
	m_Program = glCreateProgram();

	auto & shaderMan = m_Game->GetShaderManager();

	m_VertexShader = std::static_pointer_cast<const OpenGLShader>(shaderMan.Cache("shaders/vertex.vert"));
	m_FragmentShader = std::static_pointer_cast<const OpenGLShader>(shaderMan.Cache("shaders/pixel.frag"));

	_ASSERT(m_VertexShader && m_FragmentShader);

	if (m_VertexShader && m_FragmentShader)
	{
		glAttachShader(m_Program, m_VertexShader->ShaderID);
		glAttachShader(m_Program, m_FragmentShader->ShaderID);
		glBindAttribLocation(m_Program, 0, "vertexPosition");
		glBindAttribLocation(m_Program, 1, "vertexColor");
	}
	else
		m_Game->Log("Error loading shaders");

	glLinkProgram(m_Program);
	glUseProgram(m_Program);
}

void OpenGLRenderer::InitializeSampler()
{
	m_LinearSampler = 0;
	glGenSamplers(1, &m_LinearSampler);
	glSamplerParameteri(m_LinearSampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(m_LinearSampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glSamplerParameteri(m_LinearSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(m_LinearSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameterf(m_LinearSampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
}

void OpenGLRenderer::InitializeBaseTexture()
{
	const int TEXTURE_SIZE = 32;;
	const int TABLE_SIZE = 4 * TEXTURE_SIZE * TEXTURE_SIZE;
	GLfloat data[TABLE_SIZE];

	for (int i = 0; i < TABLE_SIZE; i++)
		data[i] = 1.0f;

	glGenTextures(1, &m_BaseTexture);
	glBindTexture(GL_TEXTURE_2D, m_BaseTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEXTURE_SIZE, TEXTURE_SIZE, 0, GL_FLOAT, GL_RGBA, &data);

}

Vector OpenGLRenderer::ConvertToView(const Vector & vec) const
{
	return Vector(-vec.y, vec.z, -vec.x);
}

Angle OpenGLRenderer::ConvertToView(const Angle & ang) const
{
	return Angle(ang.y, ang.z, -ang.x);
}