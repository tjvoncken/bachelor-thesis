#pragma once

#include "../../RandomProvider.h"
#include "../../../lsystem/LSystem.h"

namespace evolution
{
	/**
	* TODO!
	*/
	lsystem::LSystem* simpleBreedSystem(RandomProvider& random, const lsystem::LSystem* _a, const lsystem::LSystem* _b);
}