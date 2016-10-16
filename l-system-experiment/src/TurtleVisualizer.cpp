#include "./TurtleVisualizer.h"

#include <iostream>
#include <algorithm>

enum Heading
{
	DOWN = 0,
	LEFT = 1,
	TOP = 2,
	RIGHT = 3
};

Heading& operator++(Heading& h)
{
	int val = (int) h; val++;
	if (val == 4) { val = 0; }
	return h = Heading(val);
}

Heading& operator--(Heading& h)
{
	int val = (int) h; val--;
	if(val == 0) { val = 3; }
	return h = Heading(val);
}

void TurtleVisualizer::generate(std::list<lsystem::Token> tokens, std::list<std::pair<int, int>>& paths)
{
	auto posX = 0;
	auto posY = 0;
	auto heading = Heading::TOP;
	paths.push_back(std::pair<int, int>(0, 0));

	for (lsystem::Token token : tokens)
	{
		switch((char) token)
		{
			case TurtleVisualizer::T_LEFT:
				--heading;
				break;
			case TurtleVisualizer::T_RIGHT:
				++heading;
				break;
			case TurtleVisualizer::T_FORWARD:
				switch(heading)
				{
					case Heading::DOWN: posY--; break;
					case Heading::LEFT: posX--; break;
					case Heading::TOP: posY++; break;
					case Heading::RIGHT: posX++; break;
				}
				paths.push_back(std::pair<int, int>(posX, posY));
				break;
			default:
				// Unknown token, do nothing. :(
				break;
		}
	}
}

void TurtleVisualizer::printList(std::list<lsystem::Token> tokens)
{
	auto paths = std::list<std::pair<int, int>>();
	this->generate(tokens, paths);

	int maxX = 0;
	int maxY = 0;
	int minX = 0;
	int minY = 0;

	for(std::pair<int, int> location : paths) 
	{
		int curX = location.first; int curY = location.second;
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
			if(std::find(paths.begin(), paths.end(), std::pair<int, int>(x, y)) != paths.end()) { std::cout << ' '; }
			else { std::cout << '+'; }
		}
		std::cout << '|' << std::endl;
	}

	// Print last row.
	std::cout << '*';
	for (int x = minX; x <= maxX; x++) { std::cout << '-'; }
	std::cout << '*' << std::endl;
}