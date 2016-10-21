#include "./Point.h"

#include "./Vector.h"

namespace coordinates
{
	namespace grid
	{
		/** {@inheritdoc} */
		Point::Point(int _x, int _y) : x(_x), y(_y) {}

		/** {@inheritdoc} */
		Point::Point(const Point& _point) : x(_point.x), y(_point.y) {}

		/** {@inheritdoc} */
		Point operator+(const Point& lhs, const Vector& rhs)
		{
			return Point(lhs.x + rhs.x, lhs.y + rhs.y);
		}

		/** {@inheritdoc} */
		Point operator+(const Vector& lhs, const Point& rhs) { return rhs + lhs; }

		/** {@inheritdoc} */
		bool operator==(const Point& lhs, const Point& rhs)
		{
			return lhs.x == rhs.x
				&& lhs.y == rhs.y;
		}

		/** {@inheritdoc} */
		bool operator!=(const Point& lhs, const Point& rhs)
		{
			return !(lhs == rhs);
		}

		/** {@inheritdoc} */
		bool operator<(const Point& lhs, const Point& rhs)
		{
			return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
		}

		/** {@inheritdoc} */
		bool operator<=(const Point& lhs, const Point& rhs)
		{
			return lhs == rhs || lhs < rhs;
		}

		/** {@inheritdoc} */
		bool operator>(const Point& lhs, const Point& rhs)
		{
			return !(lhs <= rhs);
		}

		/** {@inheritdoc} */
		bool operator>=(const Point& lhs, const Point& rhs)
		{
			return !(lhs < rhs);
		}

		/** {@inheritdoc} */
		Point& Point::operator=(const Point& other) 
		{ 
			this->x = other.x;
			this->y = other.y;
			return *this;
		}

		/** {@inheritdoc} */
		Point& Point::operator+=(const Point& other) 
		{ 
			this->x += other.x;
			this->y += other.y;
			return *this;
		}
	}
}