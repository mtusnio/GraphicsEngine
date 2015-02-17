#ifndef H_IGAME
#define H_IGAME

class IGame
{
public:

	virtual void SimulatePreFrame() = 0;
	virtual void SimulatePostFrame() = 0;


};


#endif