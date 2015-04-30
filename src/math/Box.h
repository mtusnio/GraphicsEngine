#ifndef H_BOX
#define H_BOX

#include "Vector.h"

struct Box
{
	Box()
	{

	}

	// Vertice are always ordered clockwise, starting at the bottom plane left corner
	// and going clockwise, then switching to the top plane
	Box(const Vector * vertice)
	{
		for (int i = 0; i < 8; i++)
			m_Vertice[i] = vertice[i];
	}

	Box(const Vector & vec1, const Vector & vec2, const Vector & vec3, const Vector & vec4,
		const Vector & vec5, const Vector & vec6, const Vector & vec7, const Vector & vec8)
	{
		m_Vertice[0] = vec1;
		m_Vertice[1] = vec2;
		m_Vertice[2] = vec3;
		m_Vertice[3] = vec4;
		m_Vertice[4] = vec5;
		m_Vertice[5] = vec6;
		m_Vertice[6] = vec7;
		m_Vertice[7] = vec8;
	}

	const Vector & GetMinimum() const
	{
		return m_Vertice[0];
	}

	const Vector & GetMaximum() const
	{
		return m_Vertice[6];
	}

	Vector m_Vertice[8];
};

#endif