#ifndef H_IGAME
#define H_IGAME

class IScene;
struct GLFWwindow;

#include <vector>
#include "../assetmanagers/AssetManager.h"

#include "Time.h"

struct Model;
struct Texture;
struct Shader;

class IGame
{
public:
	virtual ~IGame() { };

	// Used for game initializatio and deinitialization
	virtual void Start(GLFWwindow & window) = 0;
	virtual void End() = 0;

	// Runs one frame of the game
	virtual void Run() = 0;

	// Adds a scene to the game
	virtual void AddScene(IScene * scene) = 0;

	// Removes our scene from the game, but DOES NOT delete it
	virtual void RemoveScene(IScene * scene) = 0;

	// Returns all scenes simulated in the game
	virtual const std::vector<IScene*> & GetScenes() const = 0;

	virtual AssetManager<Model> & GetModelManager() = 0;
	virtual AssetManager<Texture> & GetTextureManager() = 0;
	virtual AssetManager<Shader> & GetShaderManager() = 0;

	// Returns a structure containing all relevant time information for this frame
	virtual const Time & GetTime() const = 0;

	// Returns window this game is attached to
	virtual GLFWwindow * GetWindow() const = 0;

	// Logs a message to console
	virtual void Log(const std::string & path) = 0;
};

#endif