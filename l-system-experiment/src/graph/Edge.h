#pragma once

namespace graph
{
	class Graph;
	class Vertex;

	/**
	 * This class represents an undirected, weighted edge in a graph.
	 * Its creation and destruction are managed by the Graph object.
	 */
	class Edge
	{
		friend class Graph;

		public:
			Vertex* const a;
			Vertex* const b;
			const int weight;

		protected:
			/** An edge constructor with a default weight of 1. */
			Edge(Vertex*, Vertex*);

			/** A weighted edge constructor. */
			Edge(Vertex*, Vertex*, const int);
	};
}