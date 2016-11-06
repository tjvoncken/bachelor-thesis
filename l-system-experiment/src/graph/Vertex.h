#pragma once

#include <vector>

namespace graph
{
	class Graph;
	class Edge;

	/**
	 * This class represents a vertex in a graph. 
	 * Its creation and destruction are managed by the Graph object.
	 */
	class Vertex
	{
		friend class Graph;

		private:
			std::vector<Edge*> edges;

		protected:
			/** Yay, default constructor. */
			Vertex();

		public:
			/** Returns a vector containers pointers to all edges connecting to this vertex. */
			virtual std::vector<Edge*> getEdges();
	};
}