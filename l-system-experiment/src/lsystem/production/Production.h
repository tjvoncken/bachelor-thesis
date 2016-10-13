#pragma once

#include "../types.h"

namespace lsystem
{
	class Production
	{
		public:
			/**
			 * This function applies the production to the list if applicable.
			 * If the production is not applicable to the symbol at _position it should simply do nothing.
			 * If a production applies itself it should return true, false otherwise.
			 */
			virtual bool apply(tList& list, tList::iterator _position);
	};
}