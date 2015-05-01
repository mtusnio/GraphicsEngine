#ifndef H_GAME
#define H_GAME

#include "IGame.h"

#include <vector>

#include "../assetmanagers/ModelManager.h"
#include "../assetmanagers/LoadablesManager.h"

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
	virtual void SetActiveScene(int sceneIndex);
	virtual IScene * GetActiveScene() const { 
		if (m_Scenes.size() == 0)
			return nullptr;
		return m_Scenes[m_ActiveScene];
	}
	virtual int GetActiveSceneIndex() const { return m_ActiveScene;  }

	virtual AssetManager<Model> & GetModelManager() {return m_ModelManager; }
	virtual AssetManager<Texture> & GetTextureManager() { return *m_TextureManager; }
	virtual AssetManager<Shader> & GetShaderManager() { return *m_ShaderManager; }

	virtual const Time & GetTime() const { return m_Time; }

	virtual GLFWwindow * GetWindow() const { return m_Window; }

	virtual void Log(const std::string & msg);
private:
	// Allows derived classes to handle input at the time expected by the frame simulation
	virtual void HandleInput() { };

	virtual Vector GetRenderPosition() const;
	virtual Angle GetRenderAngle() const;

	void ClearContent();

	IRenderer * m_Renderer;

	GLFWwindow * m_Window;

	std::vector<IScene*> m_Scenes;
	int m_ActiveScene;

	ModelManager m_ModelManager;
	AssetManager<Texture> * m_TextureManager;
	AssetManager<Shader> * m_ShaderManager;

	Time m_Time;
};


#endif