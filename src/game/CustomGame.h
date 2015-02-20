#ifndef H_CUSTOMGAME
#define H_CUSTOMGAME

#include "Game.h"

class CustomGame : public Game
{
public:
	virtual void Start(GLFWwindow & window);
};

#endif