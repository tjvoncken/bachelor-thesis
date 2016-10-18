#pragma once

#include "./GraphBuilder.h"

#include <map>
#include "./MazeTurtle.h"
#include "./PointVertex.h"
#include "../coordinates/grid/Point.h"

namespace maze
{
	struct PointComparator
	{
		bool operator()(coordinates::grid::Point const& lhs, coordinates::grid::Point const& rhs) const
		{
			return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
		}
	};

	graph::Graph GraphBuilder::build(std::list<lsystem::Token> list)
	{
		auto graph = graph::Graph();
		auto turtle = maze::MazeTurtle();

		// Map for keeping track of vertex/position connection.
		auto traversed = std::map<coordinates::grid::Point, maze::PointVertex*, PointComparator>(PointComparator());

		// Vertex reference for keeping track of the previously traversed vertex.
		auto previousVertex = graph.createVertex<PointVertex>(turtle.getPosition());

		// Step count since the last vertex, for keeping track of distances.
		int stepCount = 0;

		// Save the initial position.
		traversed[turtle.getPosition()] = previousVertex;

		// Actually parse the lsystem string.
		for(auto it = list.begin(); it != list.end(); it++)
		{
			auto previousPos = turtle.getPosition();

			turtle = turtle.execute(*it);
			if(previousPos != turtle.getPosition())
			{
				//1. Increase step count.
				stepCount++;

				//2. Compare new position to already traversed positions.
				auto pos = turtle.getPosition();

				if(traversed.count(pos) == 0)
				{
					//3. If hit a position that was not hit before, make a note of it.
					traversed[pos] = 0;
				}
				else
				{
					//3. If hit a position that was hit before, create a vertex if it does not already exist.
					if(traversed[pos] == 0) { traversed[pos] = graph.createVertex<PointVertex>(pos); }
					auto vertex = traversed[pos];

					//4. Connect that vertex to the previously hit vertex.
					graph.createEdge<graph::Edge>(previousVertex, vertex, stepCount);

					//5. Set the previousVertex to the current vertex and reset the step count.
					stepCount = 0;
					previousVertex = vertex;
				}
			}
		}

		//6. Create a final vertex if the current position does not equal the previously recorded vertex.
		if(turtle.getPosition() != previousVertex->point)
		{
			auto endVertex = graph.createVertex<PointVertex>(turtle.getPosition());
			graph.createEdge<graph::Edge>(previousVertex, endVertex, stepCount);
		}

		return std::move(graph);
	}
}