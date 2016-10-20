#pragma once

#include <list>
#include <memory>
#include <vector>

#include "../language/Token.h"
#include "../production/Production.h"

namespace lsystem
{
	class RewriteEngine
	{
		private:
			using pVec = std::vector<std::unique_ptr<Production>>;
			using tList = std::list<Token>;

			pVec productions;

		public:
			/** Initializes the productions vector. */
			RewriteEngine();

			/** Adds a new production to the engine. */
			pVec::iterator addProduction(Production* const production);

			/** Removes a production from the engine. */
			std::unique_ptr<Production> removeProduction(pVec::iterator production);

			/**
			 * Rewrites the std::list of token of type A according to the rewrite rules 
			 * defined in the rewrite engine.
			 */
			tList rewrite(unsigned int iterations, tList::iterator start, tList::iterator end);
	};
}