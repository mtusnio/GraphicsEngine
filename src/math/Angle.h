#ifndef H_ANGLE
#define H_ANGLE

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
};

#endif