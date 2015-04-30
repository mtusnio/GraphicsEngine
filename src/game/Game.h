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

	ModelManager m_ModelManager;
	AssetManager<Texture> * m_TextureManager;
	AssetManager<Shader> * m_ShaderManager;

	Time m_Time;
};


#endif