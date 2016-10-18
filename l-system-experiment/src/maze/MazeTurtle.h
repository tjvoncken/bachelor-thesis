#pragma once

#include "../lsystem/language/Token.h"
#include "../coordinates/grid/grid.h"

namespace maze
{
	class MazeTurtle
	{
		private:
			MazeTurtle* previous = 0;

			coordinates::grid::Point position;
			coordinates::grid::Vector heading;

		public:
			MazeTurtle();
			MazeTurtle(MazeTurtle& turtle);

			MazeTurtle& execute(const lsystem::Token& token);

			coordinates::grid::Point getPosition();
			coordinates::grid::Vector getHeading();
	};
}