#pragma once

#include <list>
#include "./helper/MazeGraph.h"
#include "../../../lsystem/language/Token.h"

namespace maze
{
	class GraphBuilder
	{
		public:
			/** Builds a Graph object from the token list. */
			static MazeGraph build(const std::list<lsystem::Token>& tokens);

			/** Builds a Graph object from the token list. */
			static MazeGraph build(const std::list<lsystem::Token>::const_iterator begin, const std::list<lsystem::Token>::const_iterator end);
	};
}