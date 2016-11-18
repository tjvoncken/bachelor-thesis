#pragma once

#include <functional>
#include "../../lsystem/LSystem.h"

namespace evolution
{
	/**
	 * Fitness function simply returning the shortest distance from start to end.
	 * This should result in a very long, straight path through the dungeon.
	 */
	std::function<unsigned int (lsystem::LSystem*)> distanceFitnessFunction(const std::list<lsystem::Token>& input);
}