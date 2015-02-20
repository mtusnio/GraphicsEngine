#ifndef H_IGAME
#define H_IGAME

class IScene;
struct GLFWwindow;

#include <vector>

class IGame
{
public:
	// Used for game initializatio and deinitialization
	virtual void Start(GLFWwindow & window) = 0;
	virtual void End() = 0;

	// Runs one frame of the game
	virtual void Run() = 0;

	// Returns all scenes simulated in the game
	virtual const std::vector<IScene*> & GetScenes() const = 0;

};

#endif