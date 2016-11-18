#include "./simpleBreedFunction.h"

#include <random>

namespace evolution
{
	/** {@inheritdoc} */
	lsystem::LSystem* simpleBreedFunction(RandomProvider& random, const lsystem::LSystem* _a, const lsystem::LSystem* _b)
	{
		auto system = new lsystem::LSystem(*_a);

		// Average the recursion params.
		system->setRecursion((_a->getRecursion() + _b->getRecursion()) / 2);

		// Init random gen.
		auto dist = random.getRandomDistribution(1, 6); // Dice roll :D

		// Randomly mutate the recursion param.
		auto roll = dist();
		if (roll == 1 && system->getRecursion() > 1) { system->setRecursion(system->getRecursion() - 1); }
		else if (roll == 6) { system->setRecursion(system->getRecursion() + 1); }

		return system;
	};
}