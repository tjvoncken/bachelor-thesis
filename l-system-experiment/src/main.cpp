#include <iostream>
#include "./lsystem/lsystem.h"

#include "./maze/Language.h"
#include "./maze/TurtleVisualizer.h"

using Token = lsystem::Token;
using tList = lsystem::tList;

void printList(lsystem::tList output)
{
	for (auto it = output.begin(); it != output.end(); it++) { std::cout << (char) (*it); }
	std::cout << std::endl;
}

int main()
{
	lsystem::RewriteEngine engine = lsystem::RewriteEngine();

	auto p1 = new lsystem::SimpleProduction(Token('F'), std::vector<Token>({ Token('F'), Token('F') }));
	engine.addProduction(p1);

	tList input = tList({ Token('F'), Token('L'), Token('F'), Token('R'), Token('F') });

	std::cout << "Input: "; printList(input);

	auto output = engine.rewrite(1, input.begin(), input.end());

	std::cout << "Output: "; printList(output);
	
	std::cout << std::endl;
	auto visualizer = TurtleVisualizer();
	visualizer.printList(output);

	system("PAUSE");

	return 0;
}