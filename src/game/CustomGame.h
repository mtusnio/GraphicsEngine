#ifndef H_CUSTOMGAME
#define H_CUSTOMGAME

#include "Game.h"

class CustomGame : public Game
{
public:
	virtual void Start(GLFWwindow & window);

private:
	virtual void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif