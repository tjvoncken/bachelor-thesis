#pragma once

namespace graph
{
	class Graph;
	class Vertex;

	/**
	 * This class represents a directional, weighted edge in a graph.
	 * Its creation and destruction are managed by the Graph object.
	 */
	class Edge
	{
		friend class Graph;

		public:
			Vertex* const to;
			Vertex* const from;
			const int weight;

		protected:
			/** A directional edge constructor with a default weight of 1. */
			Edge(Vertex* from, Vertex* to);

			/** A directional, weighted edge constructor with a default weight of 1. */
			Edge(Vertex* from, Vertex* to, const int weight);
	};
}