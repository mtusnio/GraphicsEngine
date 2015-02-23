#ifndef H_CUSTOMGAME
#define H_CUSTOMGAME

#include "Game.h"

#include "../math/Angle.h"

class CustomGame : public Game
{
public:
	CustomGame();
	virtual ~CustomGame();

	virtual void Start(GLFWwindow & window);
private:
	virtual void HandleInput();

	virtual Vector GetRenderPosition() const { return m_RenderPosition;  }
	virtual Angle GetRenderAngle() const { return m_RenderAngle;  }

	Vector m_RenderPosition;
	Angle m_RenderAngle;

	double m_PrevX;
	double m_PrevY;
};

#endif