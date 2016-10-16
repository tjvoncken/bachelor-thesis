#pragma once

namespace coordinates
{
	namespace grid
	{
		class Point
		{
			public:
			int x = 0;
			int y = 0;

			Point(int _x, int _y);

			friend bool operator==(const Point& lhs, const Point& rhs);
			friend bool operator!=(const Point& lhs, const Point& rhs);

			Point& operator+=(const Point& point);
			friend Point operator+(Point lhs, const Point& rhs);
		};
	}
}