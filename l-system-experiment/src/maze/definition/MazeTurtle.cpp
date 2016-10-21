#include "./MazeTurtle.h"

#include <algorithm>
#include <stdexcept>
#include "./Language.h"

namespace maze
{
	/** {@inheritdoc} */
	MazeTurtle::MazeTurtle() : stack(), position(0, 0), heading(0, 1), ends(), starts() {}

	/** {@inheritdoc} */
	coordinates::grid::Point MazeTurtle::getPosition() { return this->position; }

	/** {@inheritdoc} */
	coordinates::grid::Vector MazeTurtle::getHeading() { return this->heading; }

	/** {@inheritdoc} */
	bool MazeTurtle::isStart() 
	{ 
		return std::find(this->starts.begin(), this->starts.end(), this->position) != this->starts.end(); 
	}

	/** {@inheritdoc} */
	bool MazeTurtle::isEnd() 
	{ 
		return std::find(this->ends.begin(), this->ends.end(), this->position) != this->ends.end(); 
	}

	/** {@inheritdoc} */
	void MazeTurtle::execute(const lsystem::Token& token)
	{
		switch((char) token)
		{
			case Language::T_START:
				this->starts.push_back(this->position);
				break;
			case Language::T_END:
				this->ends.push_back(this->position);
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
				else
				{
					this->position = this->stack.back().first;
					this->heading = this->stack.back().second;
					this->stack.pop_back();
				}

				break;
			default:
				throw std::runtime_error("Unknown character encountered.");
		}
	}
}