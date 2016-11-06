#pragma once

#include "./Point.h"

namespace coordinates
{
	namespace grid
	{
		/** A vector in 2D integer space. All coordinates are snapped onto the grid. */
		class Vector
		{
			/** Multiplies the vector by a scalar, effectively scaling it. */
			friend Vector operator*(const Vector& vector, const int scalar);
			friend Vector operator*(const int scalar, const Vector& vector);


			/** Add two vectors together. */
			friend Vector operator+(const Vector& lhs, const Vector& rhs);

			public:
				int x = 0;
				int y = 0;

				/** Builds a vector with length x along the x-axis and length y along the y-axis. */
				Vector(const int x, const int y);

				/** Builds a vector from point "from" to point "to". */
				Vector(const Point& from, const Point& to);

				/** Returns the length of the current vector. */
				unsigned int length() const;

				/** Rotate the vector along the z-axis (perpendicular to the 2D plane) by "angle" degrees. */
				Vector rotate(const float angle) const;

				/** Calculate the angle between this vector and another. */
				float angle(const Vector&) const;

				/** Convert the vector to a point using (0, 0) as the origin point. */
				operator coordinates::grid::Point();

				/** Copy assignment. */
				Vector& operator=(const Vector& other);

				/** Self-assignment addition operator. */
				Vector& operator+=(const Vector& other);

				/** Self-assignment multiplication operator. */
				Vector& operator*=(const int scalar);
		};
	}
}