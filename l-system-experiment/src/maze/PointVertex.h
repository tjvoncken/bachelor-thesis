#pragma once

#include "../graph/Vertex.h"
#include "../coordinates/grid/grid.h"

namespace maze
{
	class PointVertex : public graph::Vertex
	{
		public:
			const coordinates::grid::Point point;

			PointVertex(coordinates::grid::Point);
	};
}