#ifndef H_ANGLE
#define H_ANGLE

#include <math.h>
#include "consts.h"

struct Angle
{
	float x;
	float y;
	float z;

	Angle()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Angle(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Angle(const Angle & rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
	}

	Angle(const Angle && rhs) : x(std::move(rhs.x)),
		y(std::move(rhs.y)),
		z(std::move(rhs.z))
	{

	}

	Angle operator-() const
	{
		return Angle(-x, -y, -z);
	}

	Vector ToDirection() const
	{
		const float DEG2RAD = (float)Math::PI/180.f;

		float xRad = x * DEG2RAD;
		float yRad = y * DEG2RAD;
		float zRad = z * DEG2RAD;

		return Vector(cos(zRad)*cos(yRad), sin(zRad)*cos(yRad), sin(yRad));
	}
};

#endif