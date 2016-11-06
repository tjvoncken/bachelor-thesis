#pragma once

#include "./Vertex.h"

namespace graph
{
	/** {@inheritdoc} */
	Vertex::Vertex() : edges() {}

	/** {@inheritdoc} */
	std::vector<Edge*> Vertex::getEdges() const { return this->edges; }
}