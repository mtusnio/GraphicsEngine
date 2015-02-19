#ifndef H_VECTOR
#define H_VECTOR

#include <cmath>

struct Vector
{
	float x;
	float y;
	float z;

	Vector()
	{
		x = y = z = 0.0f;
	}

	Vector(const Vector & rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
	}

	Vector(const Vector && rhs) : x(std::move(rhs.x)),
		y(std::move(rhs.y)),
		z(std::move(rhs.z))
	{

	}

	Vector(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector operator +(const Vector & rhs) const
	{
		return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	Vector operator-(const Vector & rhs) const
	{
		return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	Vector operator-() const
	{
		return Vector(-x, -y, -z);
	}

	float Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	Vector Normalized() const
	{
		float length = Length();

		return Vector(x / length, y / length, z / length);
	}

	void Normalize()
	{
		float length = Length();

		x /= length;
		y /= length;
		z /= length;
	}

};

#endif