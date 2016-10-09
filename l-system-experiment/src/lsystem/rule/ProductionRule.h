#pragma once

#include <list>
#include <vector>
#include <type_traits>

namespace lsystem
{
	template <class A>
	class ProductionRule
	{
		static_assert(std::is_enum<A>::value, "A must be an enumeration.");

		public:
			virtual void apply(std::list<A>& list, typename std::list<A>::iterator _position) = NULL;
	};
}