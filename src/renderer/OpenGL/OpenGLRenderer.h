#ifndef H_OPENGLRENDERER
#define H_OPENGLRENDERER

#include "../IRenderer.h"
#include "../Model.h"

class IGame;

class OpenGLRenderer : public IRenderer
{
public:
	OpenGLRenderer(IGame & game);

	virtual void RenderScene(const IScene & scene, const Vector & cameraPosition, const Angle & cameraRotation) const;

private:
	void DrawMesh(const Model::Mesh & mesh) const;
	void DrawMeshVBOs(const Model::Mesh & mesh) const;

	void PrepareView() const;
	void InitializeProjectionMatrix(float fov, float aspect, float near, float far) const;

	void RenderObjects(const Vector & cameraPosition, const Angle & cameraRotation, const IScene & scene) const;

	// Helper methods to convert our vectors/angles into OpenGL
	void TranslateCurrentMatrix(const Vector & translation) const;
	void RotateCurrentMatrix(const Angle & rotation) const;

	Vector ConvertToView(const Vector & vec) const;
	Angle ConvertToView(const Angle & ang) const;

	IGame * m_Game;
};


#endif