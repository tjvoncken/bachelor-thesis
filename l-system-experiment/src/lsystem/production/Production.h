#pragma once

#include <list>
#include <vector>
#include <type_traits>

namespace lsystem
{
	template <typename A>
	using tIt = typename std::list<A>::iterator;

	template <class A>
	class Production
	{
		static_assert(std::is_enum<A>::value, "A must be an enumeration.");

		public:
			virtual bool apply(std::list<A>& list, tIt<A> _position) = NULL;
	};
}