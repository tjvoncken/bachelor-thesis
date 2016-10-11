#pragma once

#include <vector>
#include "./Production.h"
#include "../language/Token.h"

namespace lsystem
{
	class SimpleProduction : public Production
	{
		private:
			Token& from;
			std::vector<Token> to;

		public:
			SimpleProduction(Token& _from, std::vector<Token> _to);
			bool apply(tList& list, tList::iterator _position);
	};
}