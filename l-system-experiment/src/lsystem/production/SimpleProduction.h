#pragma once

#include "./Production.h"

namespace lsystem
{
	template <class A>
	class SimpleProduction : public Production<A>
	{
		private:
			A from;
			std::vector<A> to;

		public:
			SimpleProduction(A _from, std::vector<A> _to);
			bool apply(std::list<A>& list, tIt<A> _position);
	};

	template <class A>
	SimpleProduction<A>::SimpleProduction(A _from, std::vector<A> _to) : from(_from), to(_to) {}

	template <class A>
	bool SimpleProduction<A>::apply(std::list<A>& list, tIt<A> _position)
	{
		if ((*_position) == this->from)
		{
			list.insert(_position, this->to.begin(), this->to.end());
			return true;
		}

		return false;
	}
}