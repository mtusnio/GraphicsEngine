#ifndef H_ICOLLISIONMANAGER
#define H_ICOLLISIONMANAGER

class IPhysicsManager
{
public:
	IPhysicsManager() { }
	virtual ~IPhysicsManager() { }

	virtual void Run() = 0;
};

#endif