#pragma once

#include <list>

#include "../lsystem/language/Token.h"
#include "../coordinates/grid/grid.h"

namespace maze
{
	class MazeTurtle
	{
		private:
			using stackElement = std::pair<coordinates::grid::Point, coordinates::grid::Vector>;
			std::list<stackElement> stack;

			coordinates::grid::Point position;
			coordinates::grid::Vector heading;

		public:
			MazeTurtle();

			void execute(const lsystem::Token& token);

			coordinates::grid::Point getPosition();
			coordinates::grid::Vector getHeading();
	};
}