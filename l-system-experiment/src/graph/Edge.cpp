#pragma once

#include "./Edge.h"
#include "./Vertex.h"

namespace graph
{
	/** {@inheritdoc} */
	Edge::Edge(Vertex* _from, Vertex* _to) : Edge(_from, _to, 1) { }

	/** {@inheritdoc} */
	Edge::Edge(Vertex* _from, Vertex* _to, const int _weight) : from(_from), to(_to), weight(_weight) {}
}