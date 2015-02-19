#ifndef H_IGAME
#define H_IGAME

class IScene;
struct GLFWwindow;

class IGame
{
public:
	virtual void Start(GLFWwindow & window) = 0;
	virtual void End() = 0;

	virtual void Run() = 0;
};

#endif