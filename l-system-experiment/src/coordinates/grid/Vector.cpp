#include "./Vector.h"

#include <math.h>


namespace coordinates
{
	namespace grid
	{
		Vector::Vector(int _x, int _y) : Point(_x, _y) {}
		Vector::Vector(Point _from, Point _to) : Point(_to.x - _from.x, _to.y - _from.y) {}

		unsigned int Vector::length()
		{
			float dist = (float) round(sqrt(this->x * this->x + this->y * this->y));
			return abs((int) dist);
		}

		Vector Vector::rotate(float angle)
		{
			float sAngle = (float) sin(angle);
			float cAngle = (float) cos(angle);

			float nX = this->x * cAngle - this->y * sAngle;
			float nY = this->x * sAngle + y * cAngle;
			return Vector((int) round(nX), (int) round(nY));
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