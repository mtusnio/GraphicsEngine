#ifndef H_OPENGLRENDERER
#define H_OPENGLRENDERER

#include <glm/fwd.hpp>

#include "OpenGLHeader.h"
#include "OpenGLShader.h"

#include "../IRenderer.h"
#include "../Model.h"

class IGame;

class OpenGLRenderer : public IRenderer
{
public:
	OpenGLRenderer(IGame & game);
	virtual ~OpenGLRenderer();

	virtual void RenderScene(const IScene & scene, const Vector & cameraPosition, const Angle & cameraRotation) const;

private:
	void DrawMesh(const Model::Mesh & mesh) const;

	void BindTextures(const Material * mat) const;

	void InitializeShaders();
	void InitializeBaseTexture();
	void InitializeSampler();

	void PrepareView() const;

	void RenderObjects(const glm::mat4 & view, const glm::mat4 & projection, const IScene & scene) const;

	Vector ConvertToView(const Vector & vec) const;
	Angle ConvertToView(const Angle & ang) const;

	IGame * m_Game;

	GLuint m_Program;
	GLuint m_LinearSampler;
	GLuint m_BaseTexture;

	std::shared_ptr<const OpenGLShader> m_VertexShader;
	std::shared_ptr<const OpenGLShader> m_FragmentShader;
};


#endif