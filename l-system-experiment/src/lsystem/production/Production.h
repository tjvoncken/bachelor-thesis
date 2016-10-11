#pragma once

#include <list>
#include "../language//Token.h"

namespace lsystem
{
	using tList = typename std::list<Token>;

	class Production
	{
		public:
			virtual bool apply(tList& list, tList::iterator _position) = 0;
	};
}