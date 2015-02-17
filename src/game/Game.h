#ifndef H_GAME
#define H_GAME

#include "IGame.h"

class Game : IGame
{
public:
	Game();
	virtual ~Game();

	virtual void Start(GLFWwindow * window);
	virtual void End();

	virtual void Run();

private:
	static void GlobalKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static Game * InputHandler;

	GLFWwindow * m_Window;
	double m_StartTime;
};


#endif