#pragma once

#include <vector>
#include "./Production.h"
#include "../language/Token.h"

namespace lsystem
{
	class SimpleProduction : public Production
	{
		private:
			/** The token this production originates from. */
			Token from;

			/** The token(s) this production generates. */
			std::vector<Token> to;

		public:
			/** Constructor for this type of production. */
			SimpleProduction(Token _from, std::vector<Token> _to);

			/** Apply implementation for this type of production. */
			virtual bool apply(tList& list, tList::iterator _position) override;
	};
}