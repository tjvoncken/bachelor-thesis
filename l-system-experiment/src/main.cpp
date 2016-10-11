#include <iostream>
#include "./lsystem/RewriteEngine.h"
#include "./lsystem/language/Token.h"
#include "./lsystem/production/Production.h"
#include "./lsystem/production/SimpleProduction.h"

using Token = lsystem::Token;

void printList(lsystem::tList output)
{
	for (auto it = output.begin(); it != output.end(); it++) { std::cout << (char) (*it); }
	std::cout << std::endl;
}

int main()
{
	lsystem::RewriteEngine engine = lsystem::RewriteEngine();

	auto p1 = lsystem::SimpleProduction(Token('A'), std::vector<Token>({ Token('D'), Token('A'), Token('D') }));
	engine.addProduction(&p1);

	lsystem::tList input = lsystem::tList({ Token('B'), Token('A'), Token('A') });

	std::cout << "Input: ";
	printList(input);

	auto output = engine.rewrite(5, input.begin(), input.end());

	std::cout << "Output: ";
	printList(output);

	system("PAUSE");

	return 0;
}