#pragma once

#include <set>
#include <map>
#include "./PointVertex.h"
#include "./GraphBuilder.h"
#include "../../definition/MazeTurtle.h"

namespace maze
{
	/** {@inheritdoc} */
	graph::Graph GraphBuilder::build(const std::list<lsystem::Token>& tokens) 
	{ 
		return GraphBuilder::build(tokens.begin(), tokens.end()); 
	}

	/** {@inheritdoc} */
	graph::Graph GraphBuilder::build(const std::list<lsystem::Token>::const_iterator begin, const std::list<lsystem::Token>::const_iterator end)
	{
		auto graph = graph::Graph();
		auto turtle = maze::MazeTurtle();

		// Map for keeping track of vertex/position connection.
		auto traversed = std::map<coordinates::grid::Point, maze::PointVertex*>();

		// Vertex reference for keeping track of the previously traversed vertex.
		auto previousVertex = graph.createVertex<PointVertex>(turtle.getPosition());

		// Save the initial position.
		traversed[turtle.getPosition()] = previousVertex;

		// Actually parse the lsystem string.
		for(auto it = begin; it != end; it++)
		{
			auto previousPos = turtle.getPosition();

			turtle.execute(*it);

			auto distance = coordinates::grid::Vector(previousPos, turtle.getPosition()).length();

			if(distance > 0)
			{
				auto newPos = turtle.getPosition();

				//1. Create or find vertex at new position.
				if (traversed.count(newPos) == 0) { traversed[newPos] = graph.createVertex<PointVertex>(newPos); }
				auto newVertex = traversed[newPos];

				if(distance == 1)
				{
					//2. Link vertex to previousVertex. (Not doing that if we traversed a distance longer than 1.)
					graph.createEdge<graph::Edge>(previousVertex, newVertex, 1);
					graph.createEdge<graph::Edge>(newVertex, previousVertex, 1);
				}

				//3. Set previousPosition to the new vertex.
				previousVertex = newVertex;
			}
		}

		//4. Reduce away superfluous nodes.
		//   * Node is superfluous if there is exactly two path linking it to other nodes,
		//	   if that is the case, the node simply acts as a part of the path, and does not represent a decision.
		//TODO

		return std::move(graph);
	}
}