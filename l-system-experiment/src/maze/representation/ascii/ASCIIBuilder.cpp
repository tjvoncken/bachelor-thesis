#include "./ASCIIBuilder.h"

#include <map>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "../../definition/MazeTurtle.h"
#include "../../../coordinates/grid/Point.h"
#include "../../../coordinates/grid/Vector.h"

namespace maze
{
	enum PointType
	{
		DEFAULT = ' ',
		START = 'S',
		END = 'E',
		CONFLICT = '?'
	};

	struct PointConfig
	{
		PointType type = PointType::DEFAULT;

		bool north = false;
		bool east = false;
		bool south = false;
		bool west = false;

		PointConfig() {};
		PointConfig(const PointConfig& _conf) : type(_conf.type), north(_conf.north), east(_conf.east), 
												south(_conf.south), west(_conf.west) {};
	};

	struct MazeConfig
	{
		int minX = 0;
		int maxX = 0;
		int minY = 0;
		int maxY = 0;
	};

	std::string ASCIIBuilder::build(const std::list<lsystem::Token>& tokens) { return ASCIIBuilder::build(tokens.begin(), tokens.end()); }

	std::string ASCIIBuilder::build(const std::list<lsystem::Token>::const_iterator begin, const std::list<lsystem::Token>::const_iterator end)
	{
		using PointsMap = std::map<coordinates::grid::Point, PointConfig>;

		// A vector of all horizontal lines.
		auto points = PointsMap();
		auto turtle = MazeTurtle();
		auto mazeConfig = MazeConfig();

		points.insert(PointsMap::value_type(turtle.getPosition(), PointConfig()));

		// Build the point map.
		for(auto pos = begin; pos != end; pos++)
		{
			auto prevPos = turtle.getPosition();
			turtle.execute(*pos);
			auto newPos = turtle.getPosition();

			if(points.count(newPos) == 0) { points.insert(PointsMap::value_type(newPos, PointConfig())); }
			PointConfig& conf = points.find(newPos)->second;

			// Update type of the point.
			if (!turtle.isStart() && !turtle.isEnd()) { conf.type = PointType::DEFAULT; }
			else if(turtle.isStart() && !turtle.isEnd()) { conf.type = PointType::START; }
			else if (turtle.isEnd() && !turtle.isStart()) { conf.type = PointType::END; }
			else { conf.type = PointType::CONFLICT; }

			// Update configuration based on entrance point of turtle, ignore jumps larger than 1.
			auto prevPointConf = points.find(prevPos)->second;
			auto entraceVec = coordinates::grid::Vector(prevPos, newPos);
			if(entraceVec == coordinates::grid::Vector(0, 1)) { conf.south = true; prevPointConf.north = true; }
			else if(entraceVec == coordinates::grid::Vector(0, -1)) { conf.north = true; prevPointConf.south = true; }
			else if (entraceVec == coordinates::grid::Vector(1, 0)) { conf.west = true; prevPointConf.east = true; }
			else if (entraceVec == coordinates::grid::Vector(-1, 0)) { conf.east = true; prevPointConf.west = true; }

			// Update the maze's min/max X and Y.
			if(newPos.x < mazeConfig.minX) { mazeConfig.minX = newPos.x; }
			if(newPos.x > mazeConfig.maxX) { mazeConfig.maxX = newPos.x; }
			if(newPos.y < mazeConfig.minY) { mazeConfig.minY = newPos.y; }
			if(newPos.y > mazeConfig.maxY) { mazeConfig.maxY = newPos.y; }
		}

		// Actually build the string.
		std::stringstream buffer;

		for(auto y = mazeConfig.maxY; y >= mazeConfig.minY; y--)
		{
			// Print top dividing line.
			for(auto x = mazeConfig.minX; x <= mazeConfig.maxX; x++)
			{
				// Print top-left cell corner based on position in maze.
				if(y == mazeConfig.maxY) 
				{
					if (x == mazeConfig.minX) { buffer << char(176); } //218
					else { buffer << char(176); } //194
				}
				else 
				{
					if(x == mazeConfig.minX) { buffer << char(176); } //195
					else { buffer << char(176); } //197
				}

				auto printPos = coordinates::grid::Point(x, y);
				if(points.count(printPos) == 0) 
				{
					buffer << char(176); //196
				}
				else 
				{
					auto pointConf = points.find(printPos)->second;
					if(pointConf.north) { buffer << ' '; }
					else { buffer << char(176); } //196
				}
			}

			// Print top-right maze corner.
			if(y == mazeConfig.maxY) { buffer << char(176); } //191
			else { buffer << char(176); } //180
			buffer << std::endl;

			// Print content line.
			for (auto x = mazeConfig.minX; x <= mazeConfig.maxX; x++)
			{
				auto printPos = coordinates::grid::Point(x, y);
				if (points.count(printPos) == 0)
				{
					buffer << char(176); //179
					buffer << char(176); //178
				}
				else
				{
					auto pointConf = points.find(printPos)->second;
					if (pointConf.west) { buffer << ' '; }
					else { buffer << char(176); } //179
					buffer << (char) pointConf.type;
				}
			}

			// Print right-most maze wall.
			buffer << char(176); //179
			buffer << std::endl;
		}

		// Print bottom dividing line.
		for (auto x = mazeConfig.minX; x <= mazeConfig.maxX; x++)
		{
			buffer << char(176) << char(176);
		}

		buffer << char(176);
		buffer << std::endl;

		return buffer.str();
	}
}

/*
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
*/