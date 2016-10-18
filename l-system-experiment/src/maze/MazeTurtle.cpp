#include "./MazeTurtle.h"

#include <stdexcept>
#include "./Language.h";

namespace maze
{
	MazeTurtle::MazeTurtle() : stack(), position(0, 0), heading(0, 1) {}

	void MazeTurtle::execute(const lsystem::Token& token)
	{
		switch((char) token)
		{
			case Language::T_START:
				this->position += this->heading;
				break;
			case Language::T_END:
				this->position += this->heading;
				break;
			case Language::T_FORWARD:
				this->position += this->heading;
				break;
			case Language::T_BACKWARD:
				this->position += -1 * this->heading;
				break;
			case Language::T_LEFT:
				this->heading = this->heading.rotate(90);
				break;
			case Language::T_RIGHT:
				this->heading = this->heading.rotate(-90);
				break;
			case Language::T_PUSH:
				this->stack.push_back(stackElement(this->position, this->heading));
				break;
			case Language::T_POP:
				if(this->stack.size() <= 0) { throw std::runtime_error("Cannot POP if there has not been a PUSH."); }

				this->position = this->stack.back().first;
				this->heading = this->stack.back().second;

				break;
			default:
				throw std::runtime_error("Unknown character encountered.");
		}
	}

	coordinates::grid::Point MazeTurtle::getPosition() { return this->position; }
	coordinates::grid::Vector MazeTurtle::getHeading() { return this->heading; }
}