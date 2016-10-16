#include "./Vector.h"

#include <math.h>


namespace coordinates
{
	namespace grid
	{
		Vector::Vector(int _x, int _y) : Point(_x, _y) {}

		unsigned int Vector::length()
		{
			return sqrt(this->x * this->x + this->y * this->y);
		}

		Vector Vector::rotate(float angle)
		{
			float nX = x * cos(angle) - y * sin(angle);
			float nY = x * sin(angle) + y * cos(angle);
			return Vector(round(nX), round(nY));
		}

		Vector& Vector::operator*=(const int scalar)
		{
			this->x *= scalar;
			this->y *= scalar;
			return *this;
		}

		Vector operator*(Vector vector, const int scalar)
		{
			vector *= scalar;
			return vector;
		}

		Vector operator*(const int scalar, Vector vector) 
		{ 
			return vector * scalar; 
		}

		Vector operator+(Vector lhs, const Vector& rhs)
		{
			lhs += rhs;
			return lhs;
		}
	}
}