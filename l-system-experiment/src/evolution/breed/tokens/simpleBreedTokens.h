#pragma once

#include <memory>
#include <vector>
#include "../../RandomProvider.h"
#include "../../../lsystem/language/Token.h"

namespace evolution
{
	/**
	 * TODO!
	 */
	using TVec = std::vector<lsystem::Token>;
	TVec* simpleBreedTokens(RandomProvider& random, const TVec* _a, const TVec* _b);
}