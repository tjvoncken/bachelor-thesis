#pragma once

#include "./Vertex.h"

namespace graph
{
	Vertex::Vertex() : iEdges(), oEdges() {}

	std::vector<Edge*> Vertex::getIncomingEdges() { return this->iEdges; }
	std::vector<Edge*> Vertex::getOutgoingEdges() { return this->oEdges; }
}