#include "./Point.h"

namespace coordinates
{
	namespace grid
	{
		Point::Point(int _x, int _y) : x(_x), y(_y) {}
		Point::Point(const Point& _point) : x(_point.x), y(_point.y) {}

		Point& Point::operator+=(const Point& point)
		{
			this->x += point.x;
			this->y += point.y;
			return *this;
		}

		Point operator+(Point lhs, const Point& rhs)
		{
			lhs += rhs;
			return lhs;
		}

		bool operator==(const Point& lhs, const Point& rhs)
		{
			return lhs.x == rhs.x
				&& lhs.y == rhs.y;
		}

		bool operator!=(const Point& lhs, const Point& rhs)
		{
			return !(lhs == rhs);
		}
	}
}