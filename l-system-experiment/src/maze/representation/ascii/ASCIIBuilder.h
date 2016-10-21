#pragma once

#include <list>
#include <string>

#include "../../../lsystem/language/Token.h"

namespace maze
{
	/** Builds an ASCII version of the maze in memory. */
	class ASCIIBuilder
	{
		public:
			static std::string build(const std::list<lsystem::Token>& tokens);
			static std::string build(const std::list<lsystem::Token>::const_iterator begin, const std::list<lsystem::Token>::const_iterator end);
	};
}