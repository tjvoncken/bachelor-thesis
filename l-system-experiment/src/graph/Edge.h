#pragma once

namespace graph
{
	class Graph;
	class Vertex;

	class Edge
	{
		friend class Graph;

		public:
			Vertex* const to;
			Vertex* const from;
			const int weight;

		protected:
			Edge(Vertex* from, Vertex* to, const int weight);
	};
}