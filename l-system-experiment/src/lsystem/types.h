#pragma once

#include <list>
#include <vector>

namespace lsystem
{
	class Token;
	class Production;

	using tVec = typename std::vector<Token>;
	using tList = typename std::list<Token>;

	using pVec = std::vector<Production*>;
}