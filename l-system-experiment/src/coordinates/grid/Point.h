#pragma once

namespace coordinates
{
	namespace grid
	{
		class Vector;

		/**
		 * This class represents a single immutable point in space.
		 */
		class Point
		{
			/** Compares the x and y coordinates of two points. */
			friend bool operator==(const Point& lhs, const Point& rhs);

			/** Compares the x and y coordinates of two points. */
			friend bool operator!=(const Point& lhs, const Point& rhs);

			/** Adds a vector to a point, resulting in a new point. */
			friend Point operator+(const Point& lhs, const Vector& rhs);
			friend Point operator+(const Vector& rhs, const Point& lhs);

			/** Compares two points lexographically. */
			friend bool operator<(const Point& lhs, const Point& rhs);
			friend bool operator<=(const Point& rhs, const Point& lhs);
			friend bool operator>(const Point& rhs, const Point& lhs);
			friend bool operator>=(const Point& rhs, const Point& lhs);

			public:
				int x = 0;
				int y = 0;

				/** Constructs a new 2D Point from a x and y coordinate. */
				Point(const int x, const int y);

				/** Copy constructor for points. */
				Point(const Point&);

				/** Copy assignment. */
				Point& operator=(const Point&);

				/** Assignment addition. */
				Point& operator+=(const Point&);
		};
	}
}