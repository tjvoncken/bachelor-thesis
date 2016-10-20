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
			std::vector<Edge*> oEdges;
			std::vector<Edge*> iEdges;

		protected:
			/** Yay, default constructor. */
			Vertex();

		public:
			/** Returns a vector containers pointers to all edges incoming into this vertex. */
			virtual std::vector<Edge*> getIncomingEdges();

			/** Returns a vector containers pointers to all edges outgoing from this vertex. */
			virtual std::vector<Edge*> getOutgoingEdges();
	};
}