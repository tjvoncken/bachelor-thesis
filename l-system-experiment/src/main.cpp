#include <iostream>
#include <functional>

#include "./tests/helper.h"

#include "./evolution/breed/lsystem/simpleBreedSystem.h"
#include "./evolution/fitness/lsystem/distanceFitnessSystem.h"
#include "./evolution/fitness/lsystem/totalDistanceFitnessSystem.h"

#include "./evolution/breed/tokens/simpleBreedTokens.h"
#include "./evolution/fitness/tokens/distanceFitnessTokens.h"
#include "./evolution/fitness/tokens/totalDistanceFitnessTokens.h"

int main()
{
	// Run with the token string as representation.
	runTokenStringTest("100-shortest-distance", 100, 100000, evolution::simpleBreedTokens, evolution::distanceFitnessTokens);

	std::cout << std::endl << "*** MARKER ***" << std::endl << std::endl;

	// Run with the L-Systems as representation.
	runLSystemsTest("100-shortest-distance", 100, 10000, evolution::simpleBreedSystem, evolution::distanceFitnessSystem);

	return 0;
}