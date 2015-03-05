#ifndef H_LIGHTSOURCE
#define H_LIGHTSOURCE

#include "../math/Vector.h"
#include "../math/Angle.h"

struct LightSource
{
	Vector Position;
	Angle Rotation;
	float Color[3];
	float Intensity;
};

#endif