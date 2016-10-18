#pragma once

namespace coordinates
{
	namespace grid
	{
		class Point
		{
			friend bool operator==(const Point& lhs, const Point& rhs);
			friend bool operator!=(const Point& lhs, const Point& rhs);

			friend Point operator+(Point lhs, const Point& rhs);

			public:
				int x = 0;
				int y = 0;

				Point(int _x, int _y);

				Point& operator+=(const Point& point);
		};
	}
}