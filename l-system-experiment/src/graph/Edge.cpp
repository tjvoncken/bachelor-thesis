#pragma once

#include "./Edge.h"
#include "./Vertex.h"

namespace graph
{
	/** {@inheritdoc} */
	Edge::Edge(Vertex* _a, Vertex* _b) : Edge(_a, _b, 1) { }

	/** {@inheritdoc} */
	Edge::Edge(Vertex* _a, Vertex* _b, const int _w) : a(_a), b(_b), weight(_w) {}
}