#pragma once

#include "./GraphBuilder.h"

/*
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

		// Save the initial position.
		traversed[turtle.getPosition()] = previousVertex;

		// Actually parse the lsystem string.
		for(auto it = list.begin(); it != list.end(); it++)
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
				}

				//3. Set previousPosition to the new vertex.
				previousVertex = newVertex;
			}
		}

		//4. Reduce away superfluous nodes.
		bool change;
		do
		{
			change = false;

			auto vertices = graph.getVertices();
			for (auto it = vertices.begin(); it != vertices.end(); it++)
			{
				if ((*it)->getIncomingEdges().size() == 1 && (*it)->getOutgoingEdges().size() == 1)
				{
					// Node is superfluous, remove it and link its to and from nodes.
					graph::Edge* iEdge = (*it)->getIncomingEdges().front();
					graph::Edge* oEdge = (*it)->getOutgoingEdges().front();

					graph.createEdge<graph::Edge>(iEdge->from, oEdge->to, iEdge->weight + oEdge->weight);
					graph.removeVertex(*it);
					change = true;
					break;
				}
			}
		} 
		while(change);

		return std::move(graph);
	}
}
*/