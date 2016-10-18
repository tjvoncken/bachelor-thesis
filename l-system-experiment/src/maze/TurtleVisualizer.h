#pragma once

#include <list>
#include <string>

#include "../lsystem/lsystem.h"
#include "../coordinates/grid/Point.h"

class TurtleVisualizer
{
	private:
		using Point = coordinates::grid::Point;

	public:
		coordinates::grid::Point generate(std::list<lsystem::Token> list, std::list<Point>& paths);
		void printList(std::list<lsystem::Token> list);
};