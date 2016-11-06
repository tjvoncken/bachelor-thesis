#pragma once

#include <set>
#include <map>
#include <assert.h>

#include "./PointVertex.h"
#include "./GraphBuilder.h"

#include "../../definition/Language.h"
#include "../../definition/MazeTurtle.h"
#include "../../definition/TurtleState.h"

#include "../../../coordinates/grid/Vector.h"

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
		// Graph + turtle data structures.
		auto graph = graph::Graph();
		auto turtle = maze::MazeTurtle();

		// Lookup map for keeping track of vertex/position connection.
		using VertexMap = std::map<coordinates::grid::Point, maze::PointVertex*>;
		auto lookup = VertexMap();

		// Save the initial position.
		lookup.insert(VertexMap::value_type(turtle.getPosition(), graph.createVertex<PointVertex>(turtle.getPosition())));

		// Register movement processing functions, we're not interested in the turning at the moment, just the graph building.
		auto mvFunc = [&](const lsystem::Token&, const TurtleState& oState, const TurtleState& nState)
		{
			// oState.position should never be nState.position, since we just moved.
			assert(oState.position != nState.position);
			// Previous position should always exist as a vertex. Is always bug if it does not.
			assert(lookup.count(oState.position) != 0);

			// Check if a vertex exists for the new position, create one if it does not.
			if (lookup.count(nState.position) == 0) { lookup.insert(VertexMap::value_type(turtle.getPosition(), graph.createVertex<PointVertex>(turtle.getPosition()))); }

			// Get the vertex we're coming from, and the one we're moving to.
			auto oVertex = lookup.find(oState.position)->second;
			auto nVertex = lookup.find(nState.position)->second;

			// Link the vertices.
			graph.createEdge<graph::Edge>(oVertex, nVertex, 1);

			return nState;
		};
		turtle.registerTokenFn(lsystem::Token(Language::T_FORWARD), mvFunc);
		turtle.registerTokenFn(lsystem::Token(Language::T_BACKWARD), mvFunc);

		// Actually parse the string and create the graph.
		for(auto it = begin; it != end; it++) { turtle.execute(*it); }

		// Simplify graph by removing vertices which do nothing but interrupt an otherwise straight path.
		bool changes = false;
		do
		{
			for(auto vertex : graph.getVertices())
			{
				auto pVertex = dynamic_cast<maze::PointVertex*>(vertex);

				auto edges = vertex->getEdges();
				if(edges.size() == 2)
				{
					// Collect edges.
					auto aEdge = edges.front();
					auto bEdge = edges.back();

					// Find first vertex.
					auto aVertex = dynamic_cast<maze::PointVertex*>(aEdge->a);
					if(aEdge->a == pVertex) { aVertex = dynamic_cast<maze::PointVertex*>(aEdge->b); }

					// Find second vertex.
					auto bVertex = dynamic_cast<maze::PointVertex*>(bEdge->a);
					if (bEdge->a == pVertex) { bVertex = dynamic_cast<maze::PointVertex*>(bEdge->b); }

					// Construct movement vectors for paths between vertices.
					auto aVec = coordinates::grid::Vector(aVertex->point, pVertex->point);
					auto bVec = coordinates::grid::Vector(pVertex->point, bVertex->point);

					// If these have the same direction (angle of 0 degrees), the vertex can be removed.
					int angle = (int) round(aVec.angle(bVec));
					if(angle == 0) 
					{
						graph.createEdge<graph::Edge>(aVertex, bVertex, aEdge->weight + bEdge->weight);
						graph.removeVertex(pVertex);
					}
				}
			}
		} 
		while (changes);

		return std::move(graph);
	}
}