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

	// Accepts position & rotation in worlds coordinates, converts to OpenGL coordinate
	// system by itself
	glm::mat4 CreateModelMatrix(const Vector & position, const Angle & rotation) const;
	glm::mat4 CreateViewMatrix(const Vector & viewPosition, const Angle & viewRotation) const;


	// Converts our world space coordinates to OpenGL coordinates
	Vector ConvertToOpenGL(const Vector & vec) const;
	Angle ConvertToOpenGL(const Angle & ang) const;

	IGame * m_Game;

	OpenGLProgram m_Program;
	OpenGLProgram m_ShadowmapProgram;

	GLuint m_LinearSampler;
	GLuint m_BaseTexture;

};


#endif