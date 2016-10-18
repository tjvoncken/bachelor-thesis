#pragma once

#include "./Point.h"

namespace coordinates
{
	namespace grid
	{
		class Vector : public Point
		{
			public:
				Vector(int _x, int _y);
				Vector(Point _from, Point _to);

				unsigned int length();
				Vector rotate(float angle);

				Vector& operator*=(const int scalar);
				friend Vector operator*(Vector vector, const int scalar);
				friend Vector operator*(const int scalar, Vector vector);

				friend Vector operator+(Vector lhs, const Vector& rhs);
		};
	}
}