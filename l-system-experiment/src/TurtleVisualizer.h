#pragma once

#include <list>
#include <string>

#include "./lsystem/lsystem.h"

class TurtleVisualizer
{
	public:
		static const char T_LEFT = 'L';
		static const char T_RIGHT = 'R';
		static const char T_FORWARD = 'F';

	public:
		void generate(std::list<lsystem::Token> list, std::list<std::pair<int, int>>& paths);
		void printList(std::list<lsystem::Token> list);
};