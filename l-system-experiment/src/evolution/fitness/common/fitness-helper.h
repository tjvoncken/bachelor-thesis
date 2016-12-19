#pragma once

#include <list>

#include "../../../graph/Edge.h"
#include "../../../graph/Graph.h"
#include "../../../graph/Vertex.h"

#include "../../../maze/representation/graph/helper/MazeGraph.h"

int totalPathLength(const maze::MazeGraph& g);
int shortestPathLength(const maze::MazeGraph& g);
std::list<const graph::Edge*> dijkstra(const graph::Graph& g, const graph::Vertex* from, const graph::Vertex* to);