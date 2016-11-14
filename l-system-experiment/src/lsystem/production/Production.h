#pragma once

#include <list>
#include "../language/Token.h"

namespace lsystem
{
	class Production
	{
		protected:
			using TList = std::list<Token>;

		public:
			/** Provides a way around the limitations of the copy constructor when it comes to inheritance. */
			virtual ~Production();
			virtual Production* clone() const;

			/**
			 * This function applies the production to the list if applicable.
			 * If the production is not applicable to the symbol at the given position it should simply do nothing.
			 * If a production applies itself it should return true, false otherwise.
			 */
			virtual bool apply(TList&, TList::iterator);
	};
}