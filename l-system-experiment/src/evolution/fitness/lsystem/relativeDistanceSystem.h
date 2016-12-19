#pragma once

#include <functional>
#include "../../../lsystem/LSystem.h"

namespace evolution
{
	/** TODO */
	std::function<unsigned int(lsystem::LSystem*)> relativeDistanceFitnessSystem(const std::list<lsystem::Token>& input);
}