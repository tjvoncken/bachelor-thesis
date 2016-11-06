#include "./ASCIIBuilder.h"

#include <map>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "../../definition/Language.h"
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

		// Register start function.
		turtle.registerTokenFn
		(
			lsystem::Token(Language::T_START), 
			[&](const lsystem::Token&, const TurtleState& oState, const TurtleState& nState)
			{
				auto& pConf = points[oState.position];

				if(pConf.type == PointType::DEFAULT || pConf.type == PointType::START) { pConf.type = PointType::START; }
				else { pConf.type = PointType::CONFLICT; }

				return nState;
			}
		);

		// Register end function.
		turtle.registerTokenFn
		(
			lsystem::Token(Language::T_END),
			[&](const lsystem::Token&, const TurtleState& oState, const TurtleState& nState)
			{
				auto& pConf = points[oState.position];

				if (pConf.type == PointType::DEFAULT || pConf.type == PointType::END) { pConf.type = PointType::END; }
				else { pConf.type = PointType::CONFLICT; }

				return nState;
			}
		);

		auto mvFn = [&](const lsystem::Token&, const TurtleState& oState, const TurtleState& nState)
		{
			auto& oConf = points[oState.position];
			auto& nConf = points[nState.position];

			auto entraceVec = coordinates::grid::Vector(oState.position, nState.position);
			if (entraceVec == coordinates::grid::Vector(0, 1)) { nConf.south = true; oConf.north = true; }
			else if (entraceVec == coordinates::grid::Vector(0, -1)) { nConf.north = true; oConf.south = true; }
			else if (entraceVec == coordinates::grid::Vector(1, 0)) { nConf.west = true; oConf.east = true; }
			else if (entraceVec == coordinates::grid::Vector(-1, 0)) { nConf.east = true; oConf.west = true; }

			// Update the maze's min/max X and Y.
			if (nState.position.x < mazeConfig.minX) { mazeConfig.minX = nState.position.x; }
			if (nState.position.x > mazeConfig.maxX) { mazeConfig.maxX = nState.position.x; }
			if (nState.position.y < mazeConfig.minY) { mazeConfig.minY = nState.position.y; }
			if (nState.position.y > mazeConfig.maxY) { mazeConfig.maxY = nState.position.y; }

			return nState;
		};

		turtle.registerTokenFn(lsystem::Token(Language::T_FORWARD), mvFn);
		turtle.registerTokenFn(lsystem::Token(Language::T_BACKWARD), mvFn);
		

		// Build the point map.
		for(auto pos = begin; pos != end; pos++) { turtle.execute(*pos); }

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