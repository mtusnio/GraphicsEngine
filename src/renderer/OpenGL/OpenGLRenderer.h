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
	static const int MAX_SPOTLIGHTS = 8;
	static const int SHADOWMAP_WIDTH = 1024;
	static const int SHADOWMAP_HEIGHT = 768;
	static const float NEAR;
	static const float FAR;

	void DrawMesh(const Model::Mesh & mesh, const OpenGLProgram & program) const;

	void BindLightSources(const IScene & scene, const OpenGLProgram & program) const;
	void BindLightsForEntity(const IScene & scene, const OpenGLProgram & program, const glm::mat4 & model) const;

	void BindTextures(const Material * mat, const OpenGLProgram & program) const;

	void InitializeShaders();
	void InitializeBaseTexture();
	void InitializeShadowmapTextures();
	void InitializeSampler();

	void PrepareView() const;

	void StartRender(int width, int height) const;
	void RenderSpotlights(const IScene & scene) const;
	void RenderObjects(const glm::mat4 & view, const glm::mat4 & projection, const IScene & scene, const OpenGLProgram & program, bool lighting = false) const;

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
	GLuint m_ShadowmapTextures[MAX_SPOTLIGHTS];

	GLuint m_Framebuffer;
	GLuint m_ColorBuffer;
	GLuint m_DepthBuffer;
};


#endif