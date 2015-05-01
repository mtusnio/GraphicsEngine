#ifndef H_CUSTOMGAME
#define H_CUSTOMGAME

#include "Game.h"

#include "../math/Angle.h"

#include "../scene/LightSource.h"

#include <array>

class CustomGame : public Game
{
public:
	CustomGame();
	virtual ~CustomGame();

	virtual void Start(GLFWwindow & window);
	virtual void End();
private:
	virtual void HandleInput();

	virtual Vector GetRenderPosition() const { return m_RenderPosition;  }
	virtual Angle GetRenderAngle() const { return m_RenderAngle;  }

	Vector m_RenderPosition;
	Angle m_RenderAngle;

	SpotLightSource m_Light;
	std::array<SpotLightSource, 3> m_KeyLights;

	double m_PrevX;
	double m_PrevY;
};

#endif