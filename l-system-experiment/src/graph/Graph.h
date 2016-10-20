#pragma once

#include <memory>
#include <vector>
#include <type_traits>

#include "./Edge.h"
#include "./Vertex.h"

namespace graph
{
	/**
	 * A manager class for Graphs. This keeps track of all the vertices and edges in the graph.
	 * This class is responsible for creating edges and vertices in the Graph and deleting the pointers to them.
	 */
	class Graph
	{
		private:
			std::vector<std::unique_ptr<Edge>> edges;
			std::vector<std::unique_ptr<Vertex>> vertices;

		public:
			/** Yay, constructor. */
			Graph();

			/** Yay, destructor. */
			~Graph();

			/** Move constructor for this object moving all std::unique_ptr instances in edges and vertices. */
			Graph(Graph&&);

		private:
			/** Deleted copy constructor, since we're using std::unique_ptr, meaning this object cannot be copied. */
			Graph(const Graph&);

		public:
			/** Returns a vector containing all Edges in the graph. */
			std::vector<Edge*> getEdges();

			/** Returns a vector containing all Vertices in the graph. */
			std::vector<Vertex*> getVertices();

			/** Removes the Edge from this graph. */
			void removeEdge(Edge*);

			/**
			 * Creates a new Edge in this graph and returns a pointer to it.
			 * The arguments to this function are the same as the arguments to the constructor of Edge subclass T.
			 */
			template<typename T, typename... Args>
			T* createEdge(Args&&... args)
			{
				static_assert(std::is_base_of<Edge, T>::value, "T has to extend Edge.");

				// Create a new edge using the constructor.
				T* edge = new T(std::forward<Args>(args)...);

				// Check if to and from vertices of newly created edge are on graph, throw an error otherwise and remove the edge again.
				if(std::find(this->vertices.begin(), this->vertices.end(), edge->to) == this->vertices.end()) { delete edge; throw std::runtime_error("'to' vertex not in graph."); }
				if(std::find(this->vertices.begin(), this->vertices.end(), edge->from) == this->vertices.end()) { delete edge; throw std::runtime_error("'from' vertex not in graph."); }

				// Add the edge to the relevant vertices.
				edge->to->iEdges.push_back(edge);
				edge->from->oEdges.push_back(edge);

				// Add the edge to the graph and pass control over the pointer to a manager.
				this->edges.push_back(std::unique_ptr<Edge>(edge));
				return edge;
			}

			/** Removes the Vertex from this graph. */
			void removeVertex(Vertex*);

			/**
			 * Creates a new Vertex in this graph and returns a pointer to it.
			 * The arguments to this function are the same as the arguments to the constructor of Vertex subclass T.
			 */
			template<typename T, typename... Args>
			T* createVertex(Args&&... args)
			{
				static_assert(std::is_base_of<Vertex, T>::value, "T has to extend Vertex.");
				
				// Create a new vertex using the constructor, add it to the graph and pass control of the pointer to a manager.
				T* vertex = new T(std::forward<Args>(args)...);
				this->vertices.push_back(std::unique_ptr<Vertex>(vertex));
				return vertex;
			}
	};
}