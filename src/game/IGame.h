#ifndef H_IGAME
#define H_IGAME

class IScene;
struct GLFWwindow;

#include <vector>
#include "../assetmanagers/AssetManager.h"

struct Model;

class IGame
{
public:
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

};

#endif