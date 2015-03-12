#ifndef H_OPENGLRENDERER
#define H_OPENGLRENDERER

#include <glm/fwd.hpp>

#include "OpenGLHeader.h"
#include "OpenGLProgram.h"

#include "../IRenderer.h"
#include "../Model.h"

class IGame;
class Entity;

class OpenGLRenderer : public IRenderer
{
public:
	OpenGLRenderer(IGame & game);
	virtual ~OpenGLRenderer();

	virtual void RenderScene(const IScene & scene, const Vector & cameraPosition, const Angle & cameraRotation) const;

private:
	void DrawMesh(const Model::Mesh & mesh) const;

	void BindMatrices(const glm::mat4 & view, const glm::mat4 & projection, const Entity * ent) const;
	void BindLightSources(const IScene & scene) const;
	void BindTextures(const Material * mat) const;

	void InitializeShaders();
	void InitializeBaseTexture();
	void InitializeSampler();

	void PrepareView() const;

	void RenderObjects(const glm::mat4 & view, const glm::mat4 & projection, const IScene & scene) const;

	Vector ConverToOpenGL(const Vector & vec) const;
	Angle ConverToOpenGL(const Angle & ang) const;

	IGame * m_Game;

	OpenGLProgram m_Program;
	OpenGLProgram m_ShadowmapProgram;

	GLuint m_LinearSampler;
	GLuint m_BaseTexture;

};


#endif