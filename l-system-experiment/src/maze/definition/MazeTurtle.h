#pragma once

#include <list>
#include <vector>

#include "../../lsystem/language/Token.h"
#include "../../coordinates/grid/Point.h"
#include "../../coordinates/grid/Vector.h"

namespace maze
{
	/** An implementation of the turtle which interprets the language the l-system is based on. */
	class MazeTurtle
	{
		private:
			/** A stack for the turtle's position and heading, so it can jump back when that command is given. */
			using stackElement = std::pair<coordinates::grid::Point, coordinates::grid::Vector>;
			std::list<stackElement> stack;

			std::vector<coordinates::grid::Point> ends;
			std::vector<coordinates::grid::Point> starts;

			/** The current position of the turtle. */
			coordinates::grid::Point position;

			/** The current heading of the turtle. */
			coordinates::grid::Vector heading;

		public:
			/** A simple constructor. */
			MazeTurtle();

			/** Executes the token as a command on the turtle. Unknown or invalid tokens will throw a runtime_error. */
			void execute(const lsystem::Token& token);

			/** Returns true if the current position of the turtle is a starting point. */
			bool isStart();

			/** Returns true if the current position of the turtle is an ending point. */
			bool isEnd();

			/** Returns the current position of the turtle. */
			coordinates::grid::Point getPosition();

			/** Returns the current heading of the turtle. */
			coordinates::grid::Vector getHeading();
	};
}