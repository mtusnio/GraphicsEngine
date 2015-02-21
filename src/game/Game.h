#ifndef H_GAME
#define H_GAME

#include "IGame.h"

#include <vector>

#include "../assetmanagers/ModelManager.h"
#include "Time.h"

class IRenderer;
class IScene;

struct Vector;
struct Angle;

class Game : public IGame
{
public:
	Game();
	virtual ~Game();

	virtual void Start(GLFWwindow & window);
	virtual void End();

	virtual void Run();

	virtual void AddScene(IScene * scene);
	virtual void RemoveScene(IScene * scene);

	virtual const std::vector<IScene*> & GetScenes() const;

	virtual AssetManager<Model> & GetModelManager() {return m_ModelManager; }

	virtual const Time & GetTime() const { return m_Time; }
private:
	static void GlobalKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void GlobalCursorCallback(GLFWwindow * window, double xpos, double ypos);
	static Game * InputHandler;

	virtual void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { };
	virtual void CursorCallback(GLFWwindow * window, double xpos, double ypos) { };

	virtual Vector GetRenderPosition() const;
	virtual Angle GetRenderAngle() const;

	void ClearContent();

	IRenderer * m_Renderer;

	GLFWwindow * m_Window;

	std::vector<IScene*> m_Scenes;

	ModelManager m_ModelManager;

	Time m_Time;
};


#endif