#pragma once

#include "../../../graph/Vertex.h"
#include "../../../coordinates/grid/Point.h"

namespace maze
{
	/** Represents a vertex in the maze-graph which contains additional data like position and the fixed status of the vertex. */
	class PointVertex : public graph::Vertex
	{
		public:
			/** These vertices should not be wiped from the graph when cleaning it up. */
			const bool fixed;

			/** The point on the grid this vertex represents. */
			const coordinates::grid::Point point;

			/** Simple constructor with "fixed" defaulting to false. */
			PointVertex(coordinates::grid::Point point);

			/** Simple constructor with "fixed" as a paramter. */
			PointVertex(coordinates::grid::Point point, bool fixed);
	};
}