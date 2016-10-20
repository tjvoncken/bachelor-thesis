#include <iostream>
#include "./lsystem/lsystem.h"

#include "./graph/Vertex.h"
#include "./maze/Language.h"
#include "./maze/PointVertex.h"
#include "./maze/GraphBuilder.h"
#include "./maze/TurtleVisualizer.h"

using Token = lsystem::Token;
using tList = lsystem::tList;

void printList(lsystem::tList output)
{
	for(auto it = output.begin(); it != output.end(); it++) { std::cout << (char) (*it); }
	std::cout << std::endl;
}

int main()
{
	lsystem::RewriteEngine engine = lsystem::RewriteEngine();

	// Process L-System.
	auto p1 = new lsystem::SimpleProduction(Token('F'), std::vector<Token>({ Token('F'), Token('F'), Token('R') }));
	engine.addProduction(p1);

	auto p3 = new lsystem::SimpleProduction(Token('R'), std::vector<Token>({ Token('['), Token('F'), Token('F'), Token(']'), Token('R') }));
	engine.addProduction(p3);

	std::cout << "Processing lsystem:" << std::endl;

	tList input = tList({ Token('F'), Token('['), Token('L'), Token('F'), Token('L'), Token('F'), Token('L'), Token('F'), Token(']'), Token('F') });

	std::cout << "Input: "; printList(input);

	auto output = engine.rewrite(5, input.begin(), input.end());

	std::cout << "Output: "; printList(output);

	std::cout << std::endl;
	
	// Print maze structure.
	std::cout << "Printing maze as ASCII:" << std::endl;
	auto visualizer = TurtleVisualizer();
	visualizer.printList(output);

	std::cout << std::endl;

	// Convert maze to graph.
	std::cout << "Translating maze to graph:" << std::endl;
	auto graph = maze::GraphBuilder::build(output);

	// Orint the graph information.
	for(graph::Vertex* vertex : graph.getVertices())
	{
		auto pVertex = dynamic_cast<maze::PointVertex*>(vertex);
		std::cout << "(" << pVertex->point.x << ", " << pVertex->point.y << "):" << std::endl;

		for(graph::Edge* edge : vertex->getOutgoingEdges())
		{
			auto toVertex = dynamic_cast<maze::PointVertex*>(edge->to);
			std::cout << "-- " << edge->weight << " --> " << "(" << toVertex->point.x << ", " << toVertex->point.y << ")" << std::endl;
		}
	}

	system("PAUSE");

	return 0;
}