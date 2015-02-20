#ifndef H_GAME
#define H_GAME

#include "IGame.h"

#include <vector>

class IRenderer;
class IScene;

class Game : public IGame
{
public:
	Game();
	virtual ~Game();

	virtual void Start(GLFWwindow & window);
	virtual void End();

	virtual void Run();

	virtual const std::vector<IScene*> & GetScenes() const;


private:
	static void GlobalKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static Game * InputHandler;

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


	IRenderer * m_Renderer;

	GLFWwindow * m_Window;
	double m_StartTime;

	std::vector<IScene*> m_Scenes;
};


#endif