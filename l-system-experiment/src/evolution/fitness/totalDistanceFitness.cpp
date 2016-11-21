#include "./distanceFitnessFunction.h"

#include <map>
#include <list>
#include <vector>
#include <assert.h>
#include <algorithm>

#include "../../graph/Edge.h"
#include "../../graph/Graph.h"
#include "../../graph/Vertex.h"

#include "../../maze/representation/graph/GraphBuilder.h"
#include "../../maze/representation/graph/helper/MazeGraph.h"

namespace evolution
{
	/** Wrapper for Dijkstra's running on a MazeGraph instead of a normal Graph. */
	int shortestPathLength(const maze::MazeGraph& g);

	/** {@inheritdoc} */
	std::function<unsigned int(lsystem::LSystem*)> totalDistanceFitnessFunction(const std::list<lsystem::Token>& input)
	{
		return [&](lsystem::LSystem* system) -> unsigned int
		{
			auto string = std::list <lsystem::Token>(input);
			system->apply(string);

			auto graph = maze::GraphBuilder::build(string);

			// Punish hard for overstepping boundaries.
			if (graph.dimX > 40 || graph.dimY > 12) { return 0; }

			// Return shortest path length.
			unsigned int pathLength = shortestPathLength(graph);

			// Punish needless complexity, this should help performance a lot.
			unsigned int pathScore = 4 * pathLength * pathLength;
			unsigned int complexity = system->getRecursion() + system->getProductions().size();

			if (pathScore < complexity) { return 0; }
			else { return pathScore - complexity; }
		};
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