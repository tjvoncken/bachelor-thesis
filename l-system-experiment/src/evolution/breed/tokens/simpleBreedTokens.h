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
	using TokenString = std::vector<lsystem::Token>;
	TokenString* simpleBreedTokens(RandomProvider& random, const TokenString* _a, const TokenString* _b);
}