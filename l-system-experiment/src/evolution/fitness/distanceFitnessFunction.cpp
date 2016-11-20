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

	/** Simple implementation of Dijkstra's algorithm for finding the shortest distance from A to B. */
	std::list<const graph::Edge*> dijkstra(const graph::Graph& g, const graph::Vertex* from, const graph::Vertex* to);

	/** {@inheritdoc} */
	std::function<unsigned int (lsystem::LSystem*)> distanceFitnessFunction(const std::list<lsystem::Token>& input)
	{
		return [&](lsystem::LSystem* system)
		{
			auto string = std::list <lsystem::Token>(input);
			system->apply(string);

			auto graph = maze::GraphBuilder::build(string);

			// Punish hard for overstepping boundaries.
			if(graph.dimX > 40 || graph.dimY > 12) { return 0; }

			// Return shortest path length.
			return shortestPathLength(graph);
		};
	}

	/** {@inheritdoc} */
	int shortestPathLength(const maze::MazeGraph& g)
	{
		auto path = dijkstra(g, g.start, g.end);

		unsigned int length = 0;
		for (auto e : path) { length += e->weight; }

		return length;
	};

	/** {@inheritdoc} */
	std::list<const graph::Edge*> dijkstra(const graph::Graph& g, const graph::Vertex* from, const graph::Vertex* to)
	{
		// Set-up default environment. Processing queue, visited list and distance lookup table.
		auto visited = std::vector<const graph::Vertex*>();
		auto processing = std::vector<const graph::Vertex*>({ from });

		auto lookup = std::map<const graph::Vertex*, std::pair<int, const graph::Edge*>>();

		// Init lookup.
		auto vertices = g.getVertices();
		for (auto vertex : vertices) { lookup[vertex] = std::pair<int, const graph::Edge*>(0, 0); }

		// Actual algorithm.
		while (processing.size() > 0)
		{
			// Read, remove next-up vertex from processing queue, and add it to the visited list.
			auto vertex = processing.front();
			processing.erase(processing.begin());
			visited.push_back(vertex);

			auto edges = vertex->getEdges();
			for (auto edge : edges)
			{
				// Find the "other side" of the edge.
				auto oVertex = edge->a;
				if (edge->a == vertex) { oVertex = edge->b; }

				// Skip any edges that lead to a node that was already visited.
				if (std::find(visited.begin(), visited.end(), oVertex) != visited.end()) { continue; }

				// Push the vertex into processing if it wasn't already in there.
				if (std::find(processing.begin(), processing.end(), oVertex) == processing.end()) { processing.push_back(oVertex); }

				// Update distance to "other side" if the edge weight + the distance to current is smaller.
				auto dThis = lookup[vertex].first;
				auto dOther = lookup[oVertex].first;

				if (dOther == 0 || dThis + edge->weight < dOther)
				{
					lookup[oVertex] = std::pair<int, const graph::Edge*>(dThis + edge->weight, edge);
				}

				// If the "other side" side is the target, check if we can quit by comparing current distance to all other distances still in processing.
				if (oVertex == to)
				{
					// Current distance to target;
					auto dThis = lookup[oVertex].first;

					// Pointer to vertex still in processing which has a lower dist value: 0 < dist < oVertex.
					const graph::Vertex* other = 0;

					// Look for other vertices which still have a smaller dist value.
					for (auto vertex : processing)
					{
						auto dOther = lookup[vertex].first;
						if (dOther > 0 && dOther < dThis)
						{
							other = vertex;
							break;
						}
					}

					// If we did not find any: short circuit, we're done.
					if (other == 0) { processing.clear(); break; }
				}
			}
		}

		// Build output path list.
		auto out = std::list<const graph::Edge*>();

		auto v = to;
		while (v != from)
		{
			// Get shortes-path edge.
			auto e = lookup[v].second;

			// If e is 0, we haven't visited v yet, which should not be possible if we terminated and there is a path.
			assert(e != NULL);

			// Add edge to path.
			out.push_back(e);

			// Get "other side" vertex.
			auto oV = e->a;
			if (e->a == v) { oV = e->b; }

			// Set new "this side" vertex.
			v = oV;
		}

		// Output path list in correct order.
		out.reverse();
		return out;
	}
}