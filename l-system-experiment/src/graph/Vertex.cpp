#pragma once

#include "./Vertex.h"

namespace graph
{
	/** {@inheritdoc} */
	Vertex::Vertex() : iEdges(), oEdges() {}

	/** {@inheritdoc} */
	std::vector<Edge*> Vertex::getIncomingEdges() { return this->iEdges; }

	/** {@inheritdoc} */
	std::vector<Edge*> Vertex::getOutgoingEdges() { return this->oEdges; }
}