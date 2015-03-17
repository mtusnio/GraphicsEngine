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


const float OpenGLRenderer::NEAR = 0.25f;
const float OpenGLRenderer::FAR = 100.0f;

OpenGLRenderer::OpenGLRenderer(IGame & game)
{
	m_Game = &game;
	
	InitializeShadowmapTextures();
	InitializeBaseTexture();
	InitializeShaders();
	InitializeSampler();
}

OpenGLRenderer::~OpenGLRenderer()
{
	glDeleteTextures(MAX_SPOTLIGHTS, m_ShadowmapTextures);
	glDeleteSamplers(1, &m_LinearSampler);
	glDeleteTextures(1, &m_BaseTexture);
	glDeleteFramebuffers(1, &m_ShadowFramebuffer);
}


void OpenGLRenderer::RenderScene(const IScene & scene, const Vector & cameraPosition, const Angle & cameraRotation) const
{
	RenderShadowmaps(scene);

	int width, height;
	glfwGetFramebufferSize(m_Game->GetWindow(), &width, &height);
	float aspect = (float)width / (float)height;

	
	StartRender(0, 0, width, height);
	glCullFace(GL_BACK);
	glm::mat4 projection = glm::perspective(90.0f, aspect, NEAR, FAR);

	RenderObjects(cameraPosition, cameraRotation, projection, scene, m_Program, true);

	glfwSwapBuffers(m_Game->GetWindow());
}

void OpenGLRenderer::StartRender(int x, int y, int width, int height) const
{
	glViewport(x, y, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
}

void OpenGLRenderer::RenderShadowmaps(const IScene & scene) const
{
	auto sources = scene.GetLightSources(LightSource::SPOT);
	size_t lightCount = (int)fmin(MAX_SPOTLIGHTS, sources.size());

	glBindFramebuffer(GL_FRAMEBUFFER, m_ShadowFramebuffer);
	

	for (size_t i = 0; i < lightCount; i++)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_ShadowmapTextures[i], 0);
		glDrawBuffer(GL_NONE);
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			m_Game->Log("Frame buffer failed with " + std::to_string(status));
			_ASSERT(status == GL_FRAMEBUFFER_COMPLETE);
			break;
		}

		StartRender(0, 0, SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT);
		glCullFace(GL_FRONT);
		const SpotLightSource * light = static_cast<const SpotLightSource*>(sources[i]);
		
		glm::mat4 projection = glm::perspective(light->Cone, 1.0f, NEAR, FAR);

		RenderObjects(light->Position, light->Rotation, projection, scene, m_ShadowmapProgram, false);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLRenderer::RenderObjects(const Vector & camPosition, const Angle & camRotation, const glm::mat4 & projection, const IScene & scene, const OpenGLProgram & program, bool lighting) const
{
	glm::mat4 view = CreateViewMatrix(camPosition, camRotation);
	auto entities = scene.GetEntitySystem().GetEntities();

	glUseProgram(program.GetProgramID());

	if (lighting)
		BindLightSources(scene, program);

	Vector camPositionConv = ConvertToOpenGL(camPosition);
	glUniform3f(glGetUniformLocation(program.GetProgramID(), "cameraPosition"), camPositionConv.x, camPositionConv.y, camPositionConv.z);
	for (auto pair : entities)
	{
		Entity * ent = pair.second;
		_ASSERT(ent != nullptr);

		const Model * pModel = pair.second->GetModel();

		_ASSERT(pModel != nullptr);

		glm::mat4 model = CreateModelMatrix(ent->GetPosition(), ent->GetRotation());

		glm::mat4 MVP = projection * view * model;
		GLuint MVPLocation = glGetUniformLocation(program.GetProgramID(), "MVP");
		_ASSERT(MVPLocation != -1);

		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));
		glUniformMatrix4fv(glGetUniformLocation(program.GetProgramID(), "M"), 1, GL_FALSE, glm::value_ptr(model));

		if (lighting)
			BindLightsForEntity(scene, program, model);

		for (const Model::Mesh * mesh : pModel->Meshes)
		{
			_ASSERT(mesh != nullptr && mesh->VAOs.size() > 0);

			DrawMesh(*mesh, program);
		}

	}

}

glm::mat4 OpenGLRenderer::CreateModelMatrix(const Vector & position, const Angle & rotation) const
{
	Vector pos = ConvertToOpenGL(position);
	Angle ang = ConvertToOpenGL(rotation);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, pos.z));
	model = glm::rotate(model, glm::radians(ang.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(ang.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(ang.z), glm::vec3(0.0f, 0.0f, 1.0f));

	return model;

}

glm::mat4 OpenGLRenderer::CreateViewMatrix(const Vector & viewPosition, const Angle & viewRotation) const
{
	Vector glPos = -ConvertToOpenGL(viewPosition);
	Angle glRot = -ConvertToOpenGL(viewRotation);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::rotate(view, glm::radians(glRot.x), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, glm::radians(glRot.y), glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::rotate(view, glm::radians(glRot.z), glm::vec3(0.0f, 0.0f, 1.0f));
	view = glm::translate(view, glm::vec3(glPos.x, glPos.y, glPos.z));

	return view;
}


void OpenGLRenderer::DrawMesh(const Model::Mesh & mesh, const OpenGLProgram & program) const
{
	for (size_t i = 0; i < mesh.VAOs.size(); i++)
	{
		OpenGLVAO * vao = static_cast<OpenGLVAO*>(mesh.VAOs[i]);
		_ASSERT(vao != nullptr && vao->ID != 0);

		auto pair = mesh.Materials[i];

		BindMaterial(pair.second, program);

		glBindVertexArray(vao->ID);
		glDrawElements(GL_TRIANGLES, vao->Size, GL_UNSIGNED_INT, (void*)0);
		glBindVertexArray(0);

		// Unbind any textures we've had
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindSampler(0, 0);
	}
}

void OpenGLRenderer::BindLightSources(const IScene & scene, const OpenGLProgram & program) const
{
	auto sources = scene.GetLightSources(LightSource::SPOT);

	size_t lightCount = (int)fmin(MAX_SPOTLIGHTS, sources.size());

	glUniform1i(glGetUniformLocation(program.GetProgramID(), "SpotlightCount"), lightCount);

	for (size_t i = 0; i < lightCount; i++)
	{
		const SpotLightSource * light = static_cast<const SpotLightSource*>(sources[i]);

		_ASSERT(light != nullptr);

		std::string lightName = "Spotlights[" + std::to_string(i) + "]";
		Vector dir = ConvertToOpenGL(light->Rotation.ToDirection());
		glUniform3f(glGetUniformLocation(program.GetProgramID(), (lightName + ".Direction").c_str()), dir.x, dir.y, dir.z);
		Vector lightPosition = ConvertToOpenGL(light->Position);
		glUniform3f(glGetUniformLocation(program.GetProgramID(), (lightName + ".Position").c_str()), lightPosition.x, lightPosition.y, lightPosition.z);
		glUniform3f(glGetUniformLocation(program.GetProgramID(), (lightName + ".Color").c_str()), light->Color[0], light->Color[1], light->Color[2]);
		glUniform1f(glGetUniformLocation(program.GetProgramID(), (lightName + ".Exponent").c_str()), light->Exponent);
		glUniform1f(glGetUniformLocation(program.GetProgramID(), (lightName + ".Linear").c_str()), light->Attenuation.Linear);
		glUniform1f(glGetUniformLocation(program.GetProgramID(), (lightName + ".Constant").c_str()), light->Attenuation.Constant);
		glUniform1f(glGetUniformLocation(program.GetProgramID(), (lightName + ".Quadratic").c_str()), light->Attenuation.Quadratic);
		glUniform1f(glGetUniformLocation(program.GetProgramID(), (lightName + ".Cone").c_str()), light->Cone);
		glUniform1f(glGetUniformLocation(program.GetProgramID(), (lightName + ".MaxDistance").c_str()), light->MaxDistance);

		std::string shadowmapName = "Shadowmap[" + std::to_string(i) + "]";
		glActiveTexture(GL_TEXTURE6 + i);
		glBindTexture(GL_TEXTURE_2D, m_ShadowmapTextures[i]);
		GLuint location = glGetUniformLocation(m_Program.GetProgramID(), shadowmapName.c_str());

		glUniform1i(location, i + 6);
		
	}
	
}

void OpenGLRenderer::BindLightsForEntity(const IScene & scene, const OpenGLProgram & program, const glm::mat4 & model) const
{
	auto sources = scene.GetLightSources(LightSource::SPOT);
	size_t lightCount = (int)fmin(MAX_SPOTLIGHTS, sources.size());

	for (size_t i = 0; i < lightCount; i++)
	{
		const SpotLightSource * light = static_cast<const SpotLightSource*>(sources[i]);
		glm::mat4 view = CreateViewMatrix(light->Position, light->Rotation);
		glm::mat4 projection = glm::perspective(light->Cone, 1.0f, NEAR, FAR);

		glm::mat4 biasMatrix = glm::mat4(
			0.5f, 0.f, 0.f, 0.f,
			0.f, 0.5f, 0.f, 0.f,
			0.f, 0.f, 0.5f, 0.f,
			0.5f, 0.5f, 0.5f, 1.f);
		glm::mat4 mvp = biasMatrix * (projection * view * model);

		std::string name = "SpotlightMVP[" + std::to_string(i) + "]";
		glUniformMatrix4fv(glGetUniformLocation(program.GetProgramID(), name.c_str()), 1, GL_FALSE, glm::value_ptr(mvp));
	}
}

void OpenGLRenderer::BindMaterial(const Material * mat, const OpenGLProgram & program) const
{
	_ASSERT(mat != nullptr);
	
	BindTexture(0, mat->AmbientTex.get(), "ambientTexture", program);
	BindTexture(1, mat->DiffuseTex.get(), "diffuseTexture", program);
	BindTexture(2, mat->SpecularTex.get(), "specularTexture", program);

	glUniform3fv(glGetUniformLocation(program.GetProgramID(), "ambientIntensity"), 1, mat->Ambient);
	glUniform3fv(glGetUniformLocation(program.GetProgramID(), "diffuseIntensity"), 1, mat->Diffuse);
	glUniform3fv(glGetUniformLocation(program.GetProgramID(), "specularIntensity"), 1, mat->Specular);
	glUniform1f(glGetUniformLocation(program.GetProgramID(), "shininess"), mat->Shininess);
	
}

void OpenGLRenderer::BindTexture(int pos, const Texture * texture, const std::string & name, const OpenGLProgram & program) const
{
	const OpenGLTexture * tex = static_cast<const OpenGLTexture*>(texture);
	glUniform1i(glGetUniformLocation(program.GetProgramID(), name.c_str()), pos);

	glActiveTexture(GL_TEXTURE0 + pos);

	if (tex == nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, m_BaseTexture);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, tex->TextureID);
	}
	glBindSampler(pos, m_LinearSampler);
}

void OpenGLRenderer::InitializeShaders()
{
	auto & shaderMan = m_Game->GetShaderManager();

	m_Program.Load(std::static_pointer_cast<const OpenGLShader>(shaderMan.Cache("shaders/vertex.vert")), 
					std::static_pointer_cast<const OpenGLShader>(shaderMan.Cache("shaders/pixel.frag")));
	m_ShadowmapProgram.Load(std::static_pointer_cast<const OpenGLShader>(shaderMan.Cache("shaders/shadow.vert")),
		std::static_pointer_cast<const OpenGLShader>(shaderMan.Cache("shaders/shadow.frag")));

	_ASSERT(m_Program.GetProgramID() != 0);
	_ASSERT(m_ShadowmapProgram.GetProgramID() != 0);
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
	const int TEXTURE_SIZE = 4;
	const int TABLE_SIZE = 4 * TEXTURE_SIZE * TEXTURE_SIZE;
	GLubyte data[TABLE_SIZE];
	
	for (int i = 0; i < TABLE_SIZE; i++)
		data[i] = 255;

	glGenTextures(1, &m_BaseTexture);
	glBindTexture(GL_TEXTURE_2D, m_BaseTexture);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, TEXTURE_SIZE, TEXTURE_SIZE);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, TEXTURE_SIZE, TEXTURE_SIZE, GL_RGBA8, GL_UNSIGNED_BYTE, data);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEXTURE_SIZE, TEXTURE_SIZE, 0, GL_UNSIGNED_BYTE, GL_RGBA, data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLRenderer::InitializeShadowmapTextures()
{
	glGenFramebuffers(1, &m_ShadowFramebuffer);
	glGenTextures(MAX_SPOTLIGHTS, m_ShadowmapTextures);


	for (int i = 0; i < MAX_SPOTLIGHTS; i++)
	{
		glBindTexture(GL_TEXTURE_2D, m_ShadowmapTextures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	
}

Vector OpenGLRenderer::ConvertToOpenGL(const Vector & vec) const
{
	return Vector(-vec.y, vec.z, -vec.x);
}

Angle OpenGLRenderer::ConvertToOpenGL(const Angle & ang) const
{
	return Angle(ang.y, ang.z, -ang.x);
}