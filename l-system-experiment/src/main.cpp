#include <string>
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
	// Run for about 100 iterations to check data.
	for(unsigned int i = 44; i < 200; i++)
	{
		// Pre-fix for the iteration.
		std::string iteration = std::to_string(i);

		// POP = 100, GENS = 10000

		// Run with the tests with the shortest-distance function.
		runTokenStringTest("shortest-distance/100/" + iteration, 100, 100000, 25, evolution::simpleBreedTokens, evolution::distanceFitnessTokens);
		runLSystemsTest("shortest-distance/100/" + iteration, 100, 10000, 25, evolution::simpleBreedSystem, evolution::distanceFitnessSystem);

		// Run with the tests with the total-distance function.
		runTokenStringTest("total-distance/100/" + iteration, 100, 100000, 25, evolution::simpleBreedTokens, evolution::totalDistanceFitnessTokens);
		runLSystemsTest("total-distance/100/" + iteration, 100, 10000, 25, evolution::simpleBreedSystem, evolution::totalDistanceFitnessSystem);

		// Run with the tests with the relative-distance function.
		runTokenStringTest("relative-distance/100/" + iteration, 100, 100000, 25, evolution::simpleBreedTokens, evolution::relativeDistanceFitnessTokens);
		runLSystemsTest("relative-distance/100/" + iteration, 100, 10000, 25, evolution::simpleBreedSystem, evolution::relativeDistanceFitnessSystem);

		// POP = 500, GENS = 1000

		// Run with the tests with the shortest-distance function.
		runTokenStringTest("shortest-distance/500/" + iteration, 500, 10000, 100, evolution::simpleBreedTokens, evolution::distanceFitnessTokens);
		runLSystemsTest("shortest-distance/500/" + iteration, 500, 1000, 100, evolution::simpleBreedSystem, evolution::distanceFitnessSystem);

		// Run with the tests with the total-distance function.
		runTokenStringTest("total-distance/500/" + iteration, 500, 10000, 100, evolution::simpleBreedTokens, evolution::totalDistanceFitnessTokens);
		runLSystemsTest("total-distance/500/" + iteration, 500, 1000, 100, evolution::simpleBreedSystem, evolution::totalDistanceFitnessSystem);

		// Run with the tests with the relative-distance function.
		runTokenStringTest("relative-distance/500/" + iteration, 500, 10000, 100, evolution::simpleBreedTokens, evolution::relativeDistanceFitnessTokens);
		runLSystemsTest("relative-distance/500/" + iteration, 500, 1000, 100, evolution::simpleBreedSystem, evolution::relativeDistanceFitnessSystem);
	}

	return 0;
}