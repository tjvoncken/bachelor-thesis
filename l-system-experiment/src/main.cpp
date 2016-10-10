#include <iostream>
#include "lsystem/RewriteEngine.h"
#include "lsystem/production/SimpleProduction.h"

enum Al
{
	A = 'A',
	B = 'B',
	C = 'C',
	D = 'D'
};

template <typename A>
void printList(std::list<A> output)
{
	for (auto it = output.begin(); it != output.end(); it++) { std::cout << (char) (*it); }
	std::cout << std::endl;
}

int main()
{
	lsystem::RewriteEngine<Al> engine = lsystem::RewriteEngine<Al>();

	auto p1 = new lsystem::SimpleProduction<Al>(Al::A, std::vector<Al>({ Al::D, Al::A, Al::D }));
	engine.addProduction(p1);

	std::list<Al> input = std::list<Al>({Al::B, Al::C, Al::A});

	std::cout << "Input: ";
	printList<Al>(input);

	auto output = engine.rewrite(5, input.begin(), input.end());

	std::cout << "Output: ";
	printList<Al>(output);

	system("PAUSE");

	return 0;
}