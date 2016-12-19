#pragma once

#include <vector>
#include <functional>
#include "../../../lsystem/language/Token.h"

namespace evolution
{
	/**
	* Fitness function simply returning the shortest distance from start to end.
	* This should result in a very long, straight path through the dungeon.
	*/
	unsigned int relativeDistanceFitnessTokens(std::vector<lsystem::Token>*);
}