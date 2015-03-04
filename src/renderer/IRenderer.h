#ifndef H_IRENDERER
#define H_IRENDERER

class IScene;

struct Vector;
struct Angle;

class IRenderer
{
public:
	virtual ~IRenderer() { };

	virtual void RenderScene(const IScene & scene, const Vector & cameraPosition, const Angle & cameraRotation) const = 0;

};
#endif