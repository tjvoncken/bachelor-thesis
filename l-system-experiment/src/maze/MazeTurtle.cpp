#include "./MazeTurtle.h"

#include <stdexcept>
#include "./Language.h";

namespace maze
{
	MazeTurtle::MazeTurtle() : position(0, 0), heading(0, 1) {}

	MazeTurtle::MazeTurtle(MazeTurtle& turtle) : position(turtle.position), heading(turtle.heading)
	{
		this->previous = &turtle;
	}

	MazeTurtle& MazeTurtle::execute(lsystem::Token token)
	{
		switch((char) token)
		{
			case Language::T_FORWARD:
				this->position += this->heading;
				return *this;
			case Language::T_BACKWARD:
				this->position += -1 * this->heading;
				return *this;
			case Language::T_LEFT:
				this->heading = this->heading.rotate(90);
				return *this;
			case Language::T_RIGHT:
				this->heading = this->heading.rotate(-90);
				return *this;
			case Language::T_PUSH:
				return MazeTurtle(*this);
			case Language::T_POP:
				if(this->previous == 0) { throw std::runtime_error("Cannot POP if there has not been a PUSH."); }
				return *(this->previous);
			default:
				throw std::runtime_error("Unknown character encountered.");
		}
	}

	coordinates::grid::Point MazeTurtle::getPosition() { return this->position; }
	coordinates::grid::Vector MazeTurtle::getHeading() { return this->heading; }
}