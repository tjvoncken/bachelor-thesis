#pragma once

#include "../../coordinates/grid/Point.h"
#include "../../coordinates/grid/Vector.h"

struct TurtleState
{
	coordinates::grid::Point position;
	coordinates::grid::Vector heading;

	TurtleState() : position(0, 0), heading(0, 1) {};
	TurtleState(coordinates::grid::Point _p, coordinates::grid::Vector _h) : position(_p), heading(_h) {};
};