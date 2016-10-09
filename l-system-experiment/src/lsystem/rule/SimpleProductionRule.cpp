#include "./SimpleProductionRule.h"

namespace lsystem
{
	template <typename A>
	SimpleProductionRule<A>::SimpleProductionRule(A _from, std::vector<A> _to) : from(_from), to(_to) {}

	template <typename A>
	void SimpleProductionRule<A>::apply(std::list<A>& list, typename std::list<A>::iterator _position)
	{
		if((*_position) == this->from)
		{
			list.insert(_position, this->to.begin(), this->to.end());
		}
	}
}