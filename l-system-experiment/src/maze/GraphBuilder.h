#pragma once

#include <list>
#include "../graph/Graph.h"
#include "../lsystem/lsystem.h"

namespace maze
{
	class GraphBuilder
	{
		public:
			static graph::Graph build(std::list<lsystem::Token> list);
	};
}