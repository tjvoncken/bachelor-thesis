#pragma once

#include "./PointVertex.h"
#include "../../../../graph/Graph.h"
#include "../../../../graph/Edge.h"
#include "../../../../graph/Vertex.h"

namespace maze
{
	class MazeGraph : public graph::Graph
	{
		public:
			PointVertex* start = 0;
			PointVertex* end = 0;

			unsigned int dimX = 0;
			unsigned int dimY = 0;

		public:
			/** {@inheritdoc} */
			std::vector<PointVertex*> getVertices() const
			{ 
				auto vertices = std::vector<PointVertex*>();
				auto rVertices = Graph::getVertices();

				for(auto rVertex : rVertices) { vertices.push_back(dynamic_cast<PointVertex*>(rVertex)); }

				return vertices;
			};

			/** {@inheritdoc} */
			template<typename T, typename... Args>
			T* createVertex(Args&&... args)
			{
				static_assert(std::is_base_of<PointVertex, T>::value, "T has to extend PointVertex.");
				return Graph::createVertex<T>(std::forward<Args>(args)...);
			}
	};
}