#include "./helper.h"

#include <chrono>
#include <fstream>
#include <iostream>

#include "../evolution/MotherNature.h"
#include "../evolution/RandomProvider.h"
#include "../lsystem/production/SimpleProduction.h"
#include "../maze/representation/ascii/ASCIIBuilder.h"

/** Helper function which builds up the initial L-System population of given size. */
void buildInitialPopulation(evolution::MotherNature<lsystem::LSystem>& _nature, unsigned int _size)
{
	// Create pop vector.
	auto pop = std::vector<lsystem::LSystem*>();

	for (unsigned int i = 0; i < _size; i++)
	{
		// Init very simple L-System.
		auto system = new lsystem::LSystem();
		system->setRecursion(1);

		auto p1 = new lsystem::SimpleProduction(lsystem::Token('A'), std::vector<lsystem::Token>({ lsystem::Token('F') }));
		system->addProduction(p1);

		auto p2 = new lsystem::SimpleProduction(lsystem::Token('F'), std::vector<lsystem::Token>({ lsystem::Token('F'), lsystem::Token('F') }));
		system->addProduction(p2);

		pop.push_back(system);
	}

	// Set population into the world.
	_nature.setPopulation(pop);
}

/** @inheritdoc */
void runLSystemsTest(std::string _testName, unsigned int _population, unsigned int _generations, LSystemBreedFn _breedFn, LSystemFitnessFn _fitnessFn)
{
	// Open logging files.
	std::ofstream csvOut;
	csvOut.open("./results-systems-" + _testName + ".csv", std::ios::out | std::ios::trunc);

	std::ofstream logOut;
	csvOut.open("./results-systems-" + _testName + ".log", std::ios::out | std::ios::trunc);

	// Start timer and initialize the default input string for the system.
	auto start = std::chrono::system_clock::now();
	const std::list<lsystem::Token> input = std::list<lsystem::Token>({ lsystem::Token('S'), lsystem::Token('A'), lsystem::Token('E') });

	// Init the world.
	evolution::MotherNature<LSystem> nature(_breedFn, _fitnessFn(input));
	buildInitialPopulation(nature, 100);

	// Run for about N generations.
	auto percentageFactor = (int)(round(_generations / 100));
	auto progressFactor = (int)(round(_generations / 100));
	for (unsigned int i = 0; i < _generations; i++)
	{
		// Output progress percentages to stdout.
		if (i % percentageFactor == 0)
		{
			auto pointInTime = std::chrono::system_clock::now();
			std::chrono::duration<double> diff = pointInTime - start;
			std::cout << "Progress so far: " << i << " generations. (Running " << diff.count() << "s)" << std::endl;
		}

		// Output progress snapshot to log file.
		if (i % progressFactor == 0)
		{
			auto winnerPair = nature.getTop().front();
			auto winner = winnerPair.first;

			unsigned int fitness = winnerPair.second;
			logOut << "Top candidate after " << i << " generations with score " << fitness << ":" << std::endl;

			auto string = std::list<lsystem::Token>(input);
			winner->apply(string);
			logOut << maze::ASCIIBuilder::build(string) << std::endl;
		}

		// Write progress snapshot to CSV.
		auto winnerPair = nature.getTop().front();

		auto pointInTime = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = pointInTime - start;

		csvOut << i << ";" << diff.count() << ";" << winnerPair.second << std::endl;

		nature.evolve(75, 25);
	}

	// Output the eventual top candidate to the log, csv, and stdout.
	auto winnerPair = nature.getTop().front();
	auto winner = winnerPair.first;

	// Log final results to CSV.
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start;

	csvOut << _generations << ";" << diff.count() << ";" << winnerPair.second << std::endl;

	// Log final outcome to both stdout and the log file.
	auto string = std::list<lsystem::Token>(input);
	winner->apply(string);

	logOut << "And the winner is (after " << diff.count() << "s):" << std::endl;
	logOut << maze::ASCIIBuilder::build(string) << std::endl;

	std::cout << "And the winner is (after " << diff.count() << "s):" << std::endl;
	std::cout << maze::ASCIIBuilder::build(string) << std::endl;

	// Close all open files.
	csvOut.close();
	logOut.close();
}

/** @inheritdoc */
void runTokenStringTest(std::string _testName, unsigned int _population, unsigned int _generations, TokenStringBreedFn _breedFn, TokenStringFitnessFn _fitnessFn)
{
	// Open logging files.
	std::ofstream csvOut;
	csvOut.open("./results-tokens-" + _testName + ".csv", std::ios::out | std::ios::trunc);

	std::ofstream logOut;
	csvOut.open("./results-tokens-" + _testName + ".log", std::ios::out | std::ios::trunc);

	// Start timer.
	auto start = std::chrono::system_clock::now();

	// Init the world.
	evolution::MotherNature<TokenString> nature(_breedFn, _fitnessFn);

	// Create the initial population vector.
	auto pop = std::vector<TokenString*>();
	for (unsigned int i = 0; i < _population; i++) { pop.push_back(new TokenString({ lsystem::Token('F') })); }
	nature.setPopulation(pop);

	// Run for about N generations.
	auto percentageFactor = (int)(round(_generations / 100));
	auto progressFactor = (int)(round(_generations / 100));
	for (unsigned int i = 0; i < _generations; i++)
	{
		// Output progress percentages to stdout.
		if (i % percentageFactor == 0)
		{
			auto pointInTime = std::chrono::system_clock::now();
			std::chrono::duration<double> diff = pointInTime - start;
			std::cout << "Progress so far: " << i << " generations. (Running " << diff.count() << "s)" << std::endl;
		}

		// Output progress snapshot to log file.
		if (i % progressFactor == 0)
		{
			auto winnerPair = nature.getTop().front();
			auto winner = winnerPair.first;

			auto string = std::list<lsystem::Token>(winner->begin(), winner->end());
			string.insert(string.begin(), lsystem::Token('S'));
			string.insert(string.end(), lsystem::Token('E'));

			unsigned int fitness = winnerPair.second;
			logOut << "Top candidate after " << i << " generations with score " << fitness << ":" << std::endl;
			logOut << maze::ASCIIBuilder::build(string) << std::endl;
		}

		// Write progress snapshot to CSV.
		auto winnerPair = nature.getTop().front();
		auto pointInTime = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = pointInTime - start;

		csvOut << i << ";" << diff.count() << ";" << winnerPair.second << std::endl;

		nature.evolve(75, 25);
	}

	// Output the top candidate.
	auto winnerPair = nature.getTop().front();
	auto winner = winnerPair.first;

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start;

	// Write the final result to the CSV file.
	csvOut << _generations << ";" << diff.count() << ";" << winnerPair.second << std::endl;

	// Prepare string be pre-/appending S and E tokens.
	auto string = std::list<lsystem::Token>(winner->begin(), winner->end());
	string.insert(string.begin(), lsystem::Token('S'));
	string.insert(string.end(), lsystem::Token('E'));


	// Output the final result to both stdout and the log file.
	logOut << "And the winner is (after " << diff.count() << "s):" << std::endl;
	logOut << maze::ASCIIBuilder::build(string) << std::endl;

	std::cout << "And the winner is (after " << diff.count() << "s):" << std::endl;
	std::cout << maze::ASCIIBuilder::build(string) << std::endl;

	// Close log files.
	csvOut.close();
	logOut.close();
}