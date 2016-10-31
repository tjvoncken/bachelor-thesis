#include "./Vector.h"

#include <math.h>

namespace coordinates
{
	namespace grid
	{
		/** {@inheritdoc} */
		Vector::Vector(int _x, int _y) : x(_x), y(_y) {}

		/** {@inheritdoc} */
		Vector::Vector(const Point& _from, const Point& _to) : x(_to.x - _from.x), y(_to.y - _from.y) {}

		/** {@inheritdoc} */
		unsigned int Vector::length()
		{
			return abs(this->x + this->y);
		}

		/** {@inheritdoc} */
		Vector Vector::rotate(const float angle)
		{
			float sAngle = (float) sin(angle);
			float cAngle = (float) cos(angle);

			float nX = this->x * cAngle - this->y * sAngle;
			float nY = this->x * sAngle + y * cAngle;
			return Vector((int) round(nX), (int) round(nY));
		}

		/** {@inheritdoc} */
		Vector operator*(const Vector& vector, const int scalar)
		{
			return Vector(vector.x * scalar, vector.y * scalar);
		}

		/** {@inheritdoc} */
		Vector operator*(const int scalar, const Vector& vector) { return vector * scalar; }

		/** {@inheritdoc} */
		Vector& operator*=(const Vector& vector, const int scalar) { return vector * scalar; }

		/** {@inheritdoc} */
		Vector& operator*=(const int scalar, const Vector& vector) { return vector * scalar; }

		/** {@inheritdoc} */
		Vector operator+(const Vector& lhs, const Vector& rhs)
		{
			return Vector(lhs.x + rhs.x, lhs.y + rhs.y);
		}

		/** {@inheritdoc} */
		Vector::operator coordinates::grid::Point()
		{
			return Point(this->x, this->y);
		}

		/** {@inheritdoc} */
		Vector& Vector::operator=(const Vector& other) 
		{
			this->x = other.x;
			this->y = other.y;
			return *this;
		}

		/** {@inheritdoc} */
		Vector& Vector::operator+=(const Vector& other)
		{
			this->x += other.x;
			this->y += other.y;
			return *this;
		}

		/** {@inheritdoc} */
		Vector& Vector::operator*=(const int scalar)
		{
			this->x *= scalar;
			this->y *= scalar;
			return *this;
		}
	}
}