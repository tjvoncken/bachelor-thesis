#include <list>
#include <chrono>
#include <fstream>
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

#include "./evolution/breed/lsystem/simpleBreedSystem.h"
#include "./evolution/fitness/lsystem/distanceFitnessSystem.h"
#include "./evolution/fitness/lsystem/totalDistanceFitnessSystem.h"

#include "./evolution/breed/tokens/simpleBreedTokens.h"
#include "./evolution/fitness/tokens/distanceFitnessTokens.h"
#include "./evolution/fitness/tokens/totalDistanceFitnessTokens.h"

using Token = lsystem::Token;
using TList = std::list<lsystem::Token>;

const unsigned int GENERATIONS = 10000;

void printList(const TList& output)
{
	for(auto it = output.begin(); it != output.end(); it++) { std::cout << (char) (*it); }
	std::cout << std::endl;
}

void runTokens()
{
	std::ofstream output;
	output.open("./result-tokens.csv", std::ios::out | std::ios::trunc);

	// Timer.
	auto start = std::chrono::system_clock::now();

	// Init the world.
	//evolution::MotherNature<std::vector<lsystem::Token>> nature(evolution::simpleBreedTokens, evolution::distanceFitnessTokens);
	evolution::MotherNature<std::vector<lsystem::Token>> nature(evolution::simpleBreedTokens, evolution::totalDistanceFitnessTokens);
	
	// Create pop vector.
	auto pop = std::vector<std::vector<lsystem::Token>*>();

	for (unsigned int i = 0; i < 100; i++) { pop.push_back(new std::vector<lsystem::Token>({Token('F')})); }

	nature.setPopulation(pop);

	// Run for about 1000 generations, picking the top 100 at each generation.
	auto percentageFactor = (int)(round(GENERATIONS / 100));
	auto progressFactor = (int)(round(GENERATIONS / 100));
	for (unsigned int i = 0; i < GENERATIONS; i++)
	{
		if (i % percentageFactor == 0)
		{
			auto pointInTime = std::chrono::system_clock::now();
			std::chrono::duration<double> diff = pointInTime - start;
			std::cerr << "Progress so far: " << i << " generations. (Running " << diff.count() << "s)" << std::endl;
		}

		if (i % progressFactor == 0)
		{
			auto winnerPair = nature.getTop().front();
			auto winner = winnerPair.first;

			auto string = std::list<Token>(winner->begin(), winner->end());
			string.insert(string.begin(), lsystem::Token('S'));
			string.insert(string.end(), lsystem::Token('E'));

			unsigned int fitness = winnerPair.second;
			std::cout << "Top candidate after " << i << " generations with score " << fitness << ":" << std::endl;
			std::cout << maze::ASCIIBuilder::build(string) << std::endl;
		}

		//Write top-fitness of generation to output.
		auto winnerPair = nature.getTop().front();

		auto pointInTime = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = pointInTime - start;

		output << i << ";" << diff.count() << ";" << winnerPair.second << std::endl;

		nature.evolve(75, 25);
	}

	// Output the top candidate.
	auto winnerPair = nature.getTop().front();
	auto winner = winnerPair.first;

	auto string = std::list<Token>(winner->begin(), winner->end());
	string.insert(string.begin(), lsystem::Token('S'));
	string.insert(string.end(), lsystem::Token('E'));

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start;

	output << GENERATIONS << ";" << diff.count() << ";" << winnerPair.second << std::endl;
	output.close();

	std::cout << "And the winner is (after " << diff.count() << "s):" << std::endl;
	std::cout << maze::ASCIIBuilder::build(string) << std::endl;
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

void runLSystems()
{
	std::ofstream output;
	output.open("./result-systems.csv", std::ios::out | std::ios::trunc);

	// Timer.
	auto start = std::chrono::system_clock::now();

	// A few constants.
	const std::list<Token> input = std::list<Token>({ Token('S'), Token('A'), Token('E') });

	// Init the world.
	//evolution::MotherNature<lsystem::LSystem> nature(evolution::simpleBreedSystem, evolution::distanceFitnessSystem(input));
	evolution::MotherNature<lsystem::LSystem> nature(evolution::simpleBreedSystem, evolution::totalDistanceFitnessSystem(input));
	buildInitialPopulation(nature);

	// Run for about 1000 generations, picking the top 100 at each generation.
	auto percentageFactor = (int)(round(GENERATIONS / 100));
	auto progressFactor = (int)(round(GENERATIONS / 100));
	for (unsigned int i = 0; i < GENERATIONS; i++)
	{
		if (i % percentageFactor == 0)
		{
			auto pointInTime = std::chrono::system_clock::now();
			std::chrono::duration<double> diff = pointInTime - start;
			std::cerr << "Progress so far: " << i << " generations. (Running " << diff.count() << "s)" << std::endl;
		}

		if (i % progressFactor == 0)
		{
			auto winnerPair = nature.getTop().front();
			auto winner = winnerPair.first;

			auto string = std::list<Token>(input);
			winner->apply(string);

			unsigned int fitness = winnerPair.second;
			std::cout << "Top candidate after " << i << " generations with score " << fitness << ":" << std::endl;
			std::cout << maze::ASCIIBuilder::build(string) << std::endl;
		}

		//Write top-fitness of generation to output.
		auto winnerPair = nature.getTop().front();

		auto pointInTime = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = pointInTime - start;

		output << i << ";" << diff.count() << ";" << winnerPair.second << std::endl;

		nature.evolve(75, 25);
	}

	// Output the top candidate.
	auto winnerPair = nature.getTop().front();
	auto winner = winnerPair.first;

	auto string = std::list<Token>(input);
	winner->apply(string);

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start;

	output << GENERATIONS << ";" << diff.count() << ";" << winnerPair.second << std::endl;
	output.close();

	std::cout << "And the winner is (after " << diff.count() << "s):" << std::endl;
	std::cout << maze::ASCIIBuilder::build(string) << std::endl;
}

int main()
{
	// Run with the token string as representation.
	runTokens();

	std::cout << std::endl << "*** MARKER ***" << std::endl << std::endl;

	// Run with the L-Systems as representation.
	runLSystems();

	return 0;
}