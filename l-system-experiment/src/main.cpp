#include <iostream>
#include <functional>

#include "./tests/helper.h"

#include "./evolution/breed/lsystem/simpleBreedSystem.h"
#include "./evolution/fitness/lsystem/distanceFitnessSystem.h"
#include "./evolution/fitness/lsystem/relativeDistanceSystem.h"
#include "./evolution/fitness/lsystem/totalDistanceFitnessSystem.h"

#include "./evolution/breed/tokens/simpleBreedTokens.h"
#include "./evolution/fitness/tokens/distanceFitnessTokens.h"
#include "./evolution/fitness/tokens/relativeDistanceTokens.h"
#include "./evolution/fitness/tokens/totalDistanceFitnessTokens.h"

int main()
{
	// POP = 100, GENS = 10000

	// Run with the tests with the shortest-distance function.
	runTokenStringTest("100-shortest-distance", 100, 100000, 25, evolution::simpleBreedTokens, evolution::distanceFitnessTokens);
	runLSystemsTest("100-shortest-distance", 100, 10000, 25, evolution::simpleBreedSystem, evolution::distanceFitnessSystem);

	// Run with the tests with the total-distance function.
	runTokenStringTest("100-shortest-distance", 100, 100000, 25, evolution::simpleBreedTokens, evolution::totalDistanceFitnessTokens);
	runLSystemsTest("100-shortest-distance", 100, 10000, 25, evolution::simpleBreedSystem, evolution::totalDistanceFitnessSystem);

	// Run with the tests with the relative-distance function.
	runTokenStringTest("100-shortest-distance", 100, 100000, 25, evolution::simpleBreedTokens, evolution::relativeDistanceFitnessTokens);
	runLSystemsTest("100-shortest-distance", 100, 10000, 25, evolution::simpleBreedSystem, evolution::relativeDistanceFitnessSystem);

	// POP = 500, GENS = 1000

	// Run with the tests with the shortest-distance function.
	runTokenStringTest("500-shortest-distance", 500, 10000, 100, evolution::simpleBreedTokens, evolution::distanceFitnessTokens);
	runLSystemsTest("500-shortest-distance", 500, 1000, 100, evolution::simpleBreedSystem, evolution::distanceFitnessSystem);

	// Run with the tests with the total-distance function.
	runTokenStringTest("500-shortest-distance", 500, 10000, 100, evolution::simpleBreedTokens, evolution::totalDistanceFitnessTokens);
	runLSystemsTest("500-shortest-distance", 500, 1000, 100, evolution::simpleBreedSystem, evolution::totalDistanceFitnessSystem);

	// Run with the tests with the relative-distance function.
	runTokenStringTest("500-shortest-distance", 500, 10000, 100, evolution::simpleBreedTokens, evolution::relativeDistanceFitnessTokens);
	runLSystemsTest("500-shortest-distance", 500, 1000, 100, evolution::simpleBreedSystem, evolution::relativeDistanceFitnessSystem);

	return 0;
}