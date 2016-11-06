#pragma once

#include <map>
#include <list>
#include <vector>
#include <functional>

#include "./TurtleState.h"
#include "../../lsystem/language/Token.h"
#include "../../coordinates/grid/Point.h"
#include "../../coordinates/grid/Vector.h"

namespace maze
{
	/** An implementation of the turtle which interprets the language the l-system is based on. */
	class MazeTurtle
	{
		private:
			using TokenFn = std::function<TurtleState(const lsystem::Token&, const TurtleState&, const TurtleState&)>;

			/** Function map, mapping tokens to functions to be executed. */
			std::map<char, std::vector<TokenFn>> tokenFns;

			/** A stack for the turtle's position and heading, so it can jump back when that command is given. */
			std::list<TurtleState> stack;

			/** The current state of the turtle. */
			TurtleState state;

		public:
			/** A simple constructor. */
			MazeTurtle();

			/** Registers a function to be executed by this turtle upon reaching a matching token. */
			void registerTokenFn(const lsystem::Token, TokenFn);

			/** Executes the token as a command on the turtle. Unknown or invalid tokens will throw a runtime_error. */
			void execute(const lsystem::Token&);

			/** Returns the current position of the turtle. */
			coordinates::grid::Point getPosition();

			/** Returns the current heading of the turtle. */
			coordinates::grid::Vector getHeading();
	};
}