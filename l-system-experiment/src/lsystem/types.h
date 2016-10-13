#pragma once

#include <list>
#include <vector>
#include <memory>

namespace lsystem
{
	class Token;
	class Production;

	using tVec = typename std::vector<Token>;
	using tList = typename std::list<Token>;
}