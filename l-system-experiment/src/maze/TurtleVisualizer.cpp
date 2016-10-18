#include "./TurtleVisualizer.h"

#include <iostream>
#include <algorithm>

#include "../lsystem/lsystem.h"
#include "./MazeTurtle.h"
#include "../coordinates/grid/Point.h"

coordinates::grid::Point TurtleVisualizer::generate(std::list<lsystem::Token> tokens, std::list<Point>& paths)
{
	auto turtle = maze::MazeTurtle();
	auto current = turtle.getPosition();
	paths.push_back(current);

	for (lsystem::Token token : tokens)
	{
		turtle.execute(token);
		if(current != turtle.getPosition()) { paths.push_back(turtle.getPosition()); }
		current = turtle.getPosition();
	}

	return turtle.getPosition();
}

void TurtleVisualizer::printList(std::list<lsystem::Token> tokens)
{
	auto paths = std::list<Point>();
	auto end = this->generate(tokens, paths);

	int maxX = 0;
	int maxY = 0;
	int minX = 0;
	int minY = 0;

	for(Point location : paths) 
	{
		int curX = location.x; int curY = location.y;
		if(curX > maxX) { maxX = curX; }
		if(curY > maxY) { maxY = curY; }
		if(curX < minX) { minX = curX; }
		if(curY < minY) { minY = curY; }
	}

	// Make sure there is a border around the labyrinth.
	maxX++; maxY++; minX--; minY--;

	// Print first row.
	std::cout << '*';
	for (int x = minX; x <= maxX; x++) { std::cout << '-'; }
	std::cout << '*' << std::endl;

	// Print all rows inbetween.
	for(int y = maxY; y >= minY; y--)
	{
		std::cout << '|';
		for(int x = minX; x <= maxX; x++)
		{
			if(std::find(paths.begin(), paths.end(), Point(x, y)) != paths.end()) 
			{ 
				if (x == 0 && y == 0) { std::cout << 'S'; }
				else if(x == end.x && y == end.y) { std::cout << 'E';  }
				else { std::cout << ' '; }
			}
			else { std::cout << '+'; }
		}
		std::cout << '|' << std::endl;
	}

	// Print last row.
	std::cout << '*';
	for (int x = minX; x <= maxX; x++) { std::cout << '-'; }
	std::cout << '*' << std::endl;
}