#pragma once

#include <map>
#include <list>
#include "rule/ProductionRule.h"

namespace lsystem
{
	template <typename A>
	using tList = typename std::list<A>;

	template <typename A>
	using tIt = typename std::list<A>::iterator;

	template <typename A>
	class RewriteEngine
	{
		static_assert(std::is_enum<A>::value, "A must be an enumeration.");

		private:
			std::vector<ProductionRule<A>> rules;

		public:
			RewriteEngine();

			/**
			 * Rewrites the std::list of token of type A according to the rewrite rules 
			 * defined in the rewrite engine.
			 */
			tList<A> rewrite(unsigned int iterations, tIt<A> _start, tIt<A> _end);
	};
}