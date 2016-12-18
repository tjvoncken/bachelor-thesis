#pragma once

#include <list>
#include "../../../lsystem/language/Token.h"

namespace evolution
{
	/**
	* Fitness function simply returning the shortest distance from start to end.
	* This should result in a very long, straight path through the dungeon.
	*/
	unsigned int totalDistanceFitness(const std::list<lsystem::Token>&, unsigned int _complexity);
}