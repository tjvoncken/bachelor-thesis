#include "./totalDistanceFitness.h"

#include "./fitness-helper.h"
#include "../../../maze/representation/graph/GraphBuilder.h"

namespace evolution
{
	/** {@inheritdoc} */
	unsigned int relativeDistanceFitness(const std::list<lsystem::Token>& _tokens, unsigned int _complexity)
	{
		auto graph = maze::GraphBuilder::build(_tokens);

		// Punish hard for overstepping boundaries.
		if (graph.dimX > 40 || graph.dimY > 12) { return 0; }

		// Return shortest path length.
		unsigned int totalPath = totalPathLength(graph);
		unsigned int shortestPath = shortestPathLength(graph);

		// Punish needless complexity, this should help performance a lot.
		unsigned int pathScore = 4 * (totalPath - shortestPath) + 4 * shortestPath;
		unsigned int complexity = _complexity + _tokens.size();

		if (pathScore <= complexity) { return 0; }
		else { return pathScore - complexity; }
	}
}