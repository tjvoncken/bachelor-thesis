#pragma once

#include "./Graph.h"

namespace graph
{
	/** {@inheritdoc} */
	Graph::Graph() : edges(), vertices() {}

	/** {@inheritdoc} */
	Graph::~Graph() {}

	/** {@inheritdoc} */
	Graph::Graph(const Graph&) {}

	/** {@inheritdoc} */
	Graph::Graph(Graph&& _graph) : edges(), vertices()
	{
		for (auto it = _graph.edges.begin(); it != _graph.edges.end(); it++) { this->edges.push_back(std::move(*it)); }
		for (auto it = _graph.vertices.begin(); it != _graph.vertices.end(); it++) { this->vertices.push_back(std::move(*it)); }
	}

	/** {@inheritdoc} */
	std::vector<Edge*> Graph::getEdges() 
	{
		auto edges = std::vector<Edge*>();
		for(auto it = this->edges.begin(); it != this->edges.end(); it++) { edges.push_back(it->get()); }
		return edges;
	}

	/** {@inheritdoc} */
	std::vector<Vertex*> Graph::getVertices() 
	{
		auto vertices = std::vector<Vertex*>();
		for (auto it = this->vertices.begin(); it != this->vertices.end(); it++) { vertices.push_back(it->get()); }
		return vertices;
	}

	/** {@inheritdoc} */
	void Graph::removeEdge(Edge* _edge)
	{
		//1. Find an iterator to the edge std::unique_ptr.
		auto it = std::find_if(this->edges.begin(), this->edges.end(), [&_edge](const std::unique_ptr<Edge>& ptr) { return ptr.get() == _edge; });
		if(it == this->edges.end()) { throw std::runtime_error("Edge not found within graph. Cannot remove it."); }

		//2. Remove the edge from its a vertex.
		std::vector<Edge*>& aEdges = (*it)->a->edges;
		auto aeit = std::find(aEdges.begin(), aEdges.end(), _edge);
		if (aeit == aEdges.end()) { throw std::runtime_error("SANITY_CHECK"); }
		aEdges.erase(aeit);

		//3. Remove the edge from its b vertex.
		std::vector<Edge*>& bEdges = (*it)->b->edges;
		auto beit = std::find(bEdges.begin(), bEdges.end(), _edge);
		if (beit == bEdges.end()) { throw std::runtime_error("SANITY_CHECK"); }
		bEdges.erase(beit);

		//4. Remove the edge from std::vector edges.
		this->edges.erase(it);
	}

	/** {@inheritdoc} */
	void Graph::removeVertex(Vertex* _vertex)
	{
		//1. Find an iterator to the vertex std::unique_ptr.
		auto it = std::find_if(this->vertices.begin(), this->vertices.end(), [&_vertex](const std::unique_ptr<Vertex>& ptr) { return ptr.get() == _vertex; });
		if (it == this->vertices.end()) { throw std::runtime_error("Edge not found within graph. Cannot remove it."); }

		//2. Remove the edges coming from and going to the vertex.
		for(Edge* e : std::vector<Edge*>((*it)->edges)) { this->removeEdge(e); }

		//3. Remove the vertex from std::vector vertices.
		this->vertices.erase(it);
	}
}