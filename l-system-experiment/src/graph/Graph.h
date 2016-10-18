#pragma once

#include <memory>
#include <vector>
#include <type_traits>

#include "./Edge.h"
#include "./Vertex.h"

namespace graph
{
	class Graph
	{
		private:
			std::vector<std::unique_ptr<Edge>> edges;
			std::vector<std::unique_ptr<Vertex>> vertices;

		public:
			Graph();
			~Graph();
			Graph(Graph&&);

		private:
			Graph(const Graph&);

		public:
			std::vector<Edge*> getEdges();
			std::vector<Vertex*> getVertices();

			void removeEdge(Edge*);
			void removeVertex(Vertex*);

			template<typename T, typename... Args>
			T* createEdge(Args&&... args)
			{
				static_assert(std::is_base_of<Edge, T>::value, "T has to extend Edge.");

				T* edge = new T(std::forward<Args>(args)...);

				//TODO: ensure the vertices are part of the graph.
				edge->to->iEdges.push_back(edge);
				edge->from->oEdges.push_back(edge);

				this->edges.push_back(std::unique_ptr<Edge>(edge));
				return edge;
			}

			template<typename T, typename... Args>
			T* createVertex(Args&&... args)
			{
				static_assert(std::is_base_of<Vertex, T>::value, "T has to extend Vertex.");
				
				T* vertex = new T(std::forward<Args>(args)...);
				this->vertices.push_back(std::unique_ptr<Vertex>(vertex));
				return vertex;
			}
	};
}