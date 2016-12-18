#include "./totalDistanceFitness.h"

#include <list>

#include "../../../graph/Edge.h"
#include "../../../graph/Graph.h"
#include "../../../graph/Vertex.h"

#include "../../../maze/representation/graph/GraphBuilder.h"
#include "../../../maze/representation/graph/helper/MazeGraph.h"

namespace evolution
{
	/** Wrapper for Dijkstra's running on a MazeGraph instead of a normal Graph. */
	int totalPathLength(const maze::MazeGraph& g);

	/** {@inheritdoc} */
	unsigned int totalDistanceFitness(const std::list<lsystem::Token>& _tokens, unsigned int _complexity)
	{
		auto graph = maze::GraphBuilder::build(_tokens);

		// Punish hard for overstepping boundaries.
		if (graph.dimX > 40 || graph.dimY > 12) { return 0; }

		// Return shortest path length.
		unsigned int pathLength = totalPathLength(graph);

		// Punish needless complexity, this should help performance a lot.
		unsigned int pathScore = 4 * pathLength * pathLength;

		if (pathScore <= _complexity) { return 0; }
		else { return pathScore - _complexity; }
	}

	/** {@inheritdoc} */
	int totalPathLength(const maze::MazeGraph& g)
	{
		auto edges = g.getEdges();

		unsigned int length = 0;
		for (auto e : edges) { length += e->weight; }

		return length;
	};
}