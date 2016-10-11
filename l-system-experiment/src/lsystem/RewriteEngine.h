#pragma once

#include <map>
#include <list>
#include <vector>

#include "production/Production.h"

namespace lsystem
{
	using pVec = std::vector<Production*>;

	class RewriteEngine
	{
		private:
			pVec productions;

		public:
			/** Initializes the productions vector. */
			RewriteEngine();

			/** Adds a new production to the engine. */
			pVec::iterator addProduction(Production* _production);

			/** Removes a production from the engine. */
			void removeProduction(pVec::iterator _production);

			/**
			 * Rewrites the std::list of token of type A according to the rewrite rules 
			 * defined in the rewrite engine.
			 */
			tList rewrite(unsigned int iterations, tList::iterator _start, tList::iterator _end);
	};
}