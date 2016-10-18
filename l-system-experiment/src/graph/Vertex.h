#pragma once

#include <vector>

namespace graph
{
	class Graph;
	class Edge;

	class Vertex
	{
		friend class Graph;

		private:
			std::vector<Edge*> oEdges;
			std::vector<Edge*> iEdges;

		protected:
			Vertex();

		public:
			virtual std::vector<Edge*> getIncomingEdges();
			virtual std::vector<Edge*> getOutgoingEdges();
	};
}