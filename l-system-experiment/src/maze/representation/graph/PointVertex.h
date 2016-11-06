#pragma once

#include "./VertexType.h"
#include "../../../graph/Vertex.h"
#include "../../../coordinates/grid/Point.h"

namespace maze
{
	/** Represents a vertex in the maze-graph which contains additional data like position and the fixed status of the vertex. */
	class PointVertex : public graph::Vertex
	{
		public:
			/** Type of the Vertex. This marks start and end vertices and prevents them from being wiped from the map. */
			VertexType type;

			/** The point on the grid this vertex represents. */
			coordinates::grid::Point point;

			/** Simple constructor with the type defaulting to DEFAULT. */
			PointVertex(const coordinates::grid::Point point);

			/** Simple constructor with the type as a parameter. */
			PointVertex(const coordinates::grid::Point point, const VertexType type);
	};
}