#pragma once

namespace maze
{
	enum Language
	{
		// Movement instructions.
		T_FORWARD = 'F',	// Move the turtle forwards.
		T_BACKWARD = 'B',	// Move the turtle backwards.

		// Heading instructions.
		T_LEFT = 'L',		// Turn the turtle left.
		T_RIGHT = 'R',		// Turn the turtle right.

		// Branching instructions.
		T_PUSH = '[',		// Push the state of the turtle onto a stack.
		T_POP = ']'			// Pop the previously pushed state of the turtle from the stack.
	};
}