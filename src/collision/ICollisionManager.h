#ifndef H_ICOLLISIONMANAGER
#define H_ICOLLISIONMANAGER

class ICollisionManager
{
public:
	ICollisionManager() { }
	virtual ~ICollisionManager() { }

	virtual void Run() = 0;
};

#endif