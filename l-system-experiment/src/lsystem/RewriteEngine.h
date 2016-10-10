#pragma once

#include <map>
#include <list>
#include "production/Production.h"

namespace lsystem
{
	template <typename A>
	using tList = typename std::list<A>;

	template <typename A>
	using tIt = typename std::list<A>::iterator;

	template <class A>
	class RewriteEngine
	{
		/** Make sure the language is always an enumeration of tokens. */
		static_assert(std::is_enum<A>::value, "A must be an enumeration.");

		private:
			std::vector<Production<A>*> productions;

		public:
			/** Initializes the productions vector. */
			RewriteEngine();

			void addProduction(Production<A>* _production);

			/**
			 * Rewrites the std::list of token of type A according to the rewrite rules 
			 * defined in the rewrite engine.
			 */
			tList<A> rewrite(unsigned int iterations, tIt<A> _start, tIt<A> _end);
	};

	template <class A>
	RewriteEngine<A>::RewriteEngine() : productions() {}

	template <class A>
	void RewriteEngine<A>::addProduction(Production<A>* _production)
	{
		this->productions.insert(this->productions.end(), _production);
	}

	template <class A>
	tList<A> RewriteEngine<A>::rewrite(unsigned int iterations, tIt<A> _start, tIt<A> _end)
	{
		tList<A> buffer = tList<A>(_start, _end);

		if (iterations == 0) { return buffer; }
		else
		{
			auto it = buffer.begin();
			while(it != buffer.end())
			{
				bool pRan = false;
				for(auto pIt = this->productions.begin(); pIt != this->productions.end(); pIt++)
				{
					pRan = pRan || (*pIt)->apply(buffer, it);
				}

				if(pRan) { it = buffer.erase(it); }
				else { it++; }
			}

			return rewrite(iterations - 1, buffer.begin(), buffer.end());
		}
	}
}