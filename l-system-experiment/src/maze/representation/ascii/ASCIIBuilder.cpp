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
			PointConfig& prevPointConf = points.find(prevPos)->second;
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
				buffer << char(176);

				auto printPos = coordinates::grid::Point(x, y);
				if(points.count(printPos) == 0) { buffer << char(176); }
				else 
				{
					auto pointConf = points.find(printPos)->second;
					if(pointConf.north) { buffer << ' '; }
					else { buffer << char(176); }
				}
			}

			// Print top-right maze corner.
			buffer << char(176) << std::endl;

			// Print content line.
			for (auto x = mazeConfig.minX; x <= mazeConfig.maxX; x++)
			{
				auto printPos = coordinates::grid::Point(x, y);
				if (points.count(printPos) == 0)
				{
					buffer << char(176) << char(176);
				}
				else
				{
					auto pointConf = points.find(printPos)->second;

					if (pointConf.west) { buffer << ' '; }
					else { buffer << char(176); }
					buffer << (char) pointConf.type;
				}
			}

			// Print right-most maze wall.
			buffer << char(176) << std::endl;
		}

		// Print bottom dividing line.
		for (auto x = mazeConfig.minX; x <= mazeConfig.maxX; x++) { buffer << char(176) << char(176); }
		buffer << char(176) << std::endl;

		return buffer.str();
	}
}