#pragma once

#include <list>
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
			virtual ~SimpleProduction();
			virtual SimpleProduction* clone() const;

			/** Constructor for this type of production. */
			SimpleProduction(Token from, std::vector<Token> to);

			/** Apply implementation for this type of production. */
			virtual bool apply(TList&, TList::iterator) override;
	};
}