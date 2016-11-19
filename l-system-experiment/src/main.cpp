#include <list>
#include <chrono>
#include <iostream>
#include <functional>

#include "./lsystem/LSystem.h"
#include "./lsystem/production/SimpleProduction.h"

#include "./maze/definition/Language.h"
#include "./maze/representation/graph/helper/VertexType.h"
#include "./maze/representation/graph/helper/PointVertex.h"
#include "./maze/representation/graph/GraphBuilder.h"
#include "./maze/representation/ascii/ASCIIBuilder.h"

#include "./evolution/MotherNature.h"
#include "./evolution/breed/simpleBreedFunction.h"
#include "./evolution/fitness/distanceFitnessFunction.h"

using Token = lsystem::Token;
using TList = std::list<lsystem::Token>;

void printList(const TList& output)
{
	for(auto it = output.begin(); it != output.end(); it++) { std::cout << (char) (*it); }
	std::cout << std::endl;
}

void buildInitialPopulation(evolution::MotherNature<lsystem::LSystem>& nature)
{
	// Create pop vector.
	auto pop = std::vector<lsystem::LSystem*>();

	for(unsigned int i = 0; i < 100; i++)
	{
		// Init very simple L-System.
		auto system = new lsystem::LSystem();
		system->setRecursion(1);

		auto p1 = new lsystem::SimpleProduction(Token('A'), std::vector<Token>({ Token('F') }));
		system->addProduction(p1);

		auto p2 = new lsystem::SimpleProduction(Token('F'), std::vector<Token>({ Token('F'), Token('F') }));
		system->addProduction(p2);

		pop.push_back(system);
	}

	// Set population into the world.
	nature.setPopulation(pop);
}

int main()
{
	// Timer.
	auto start = std::chrono::system_clock::now();

	// A few constants.
	const unsigned int GENERATIONS = 1000;
	const std::list<Token> input = std::list<Token>({ Token('S'), Token('A'), Token('E') });

	// Init the world.
	evolution::MotherNature<lsystem::LSystem> nature(evolution::simpleBreedFunction, evolution::distanceFitnessFunction(input));
	buildInitialPopulation(nature);

	// Run for about 1000 generations, picking the top 100 at each generation.
	auto percentageFactor = (int) (round(GENERATIONS / 100));
	auto progressFactor = (int) (round(GENERATIONS / 100));
	for(unsigned int i = 0; i < GENERATIONS; i++)
	{
		if(i % percentageFactor == 0) 
		{
			auto pointInTime = std::chrono::system_clock::now();
			std::chrono::duration<double> diff = pointInTime - start;
			std::cout << "Progress so far: " << i << " generations. (Running " << diff.count() << "s)" << std::endl;
		}

		if(i % progressFactor == 0)
		{
			auto winner = nature.getTop().front();

			auto string = std::list<Token>(input);
			winner->apply(string);

			std::cout << "Top candidate after " << i << " generations:" << std::endl;
			std::cout << maze::ASCIIBuilder::build(string) << std::endl;
		}

		nature.evolve(10);
	}

	// Output the top candidate.
	auto winner = nature.getTop().front();

	auto string = std::list<Token>(input);
	winner->apply(string);

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start;

	std::cout << "And the winner is (after " << diff.count() << "s):" << std::endl;
	std::cout << maze::ASCIIBuilder::build(string) << std::endl;

	std::system("PAUSE"); return 0;
}