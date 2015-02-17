#ifndef H_IGAME
#define H_IGAME

class IEntitySystem;

class IScene
{
public:

	virtual void SimulatePreFrame() = 0;
	virtual void SimulatePostFrame() = 0;

	virtual IEntitySystem * GetEntitySystem() = 0;
};


#endif