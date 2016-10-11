#include "./SimpleProduction.h"

namespace lsystem
{
	/** {@inheritdoc} */
	SimpleProduction::SimpleProduction(Token _from, std::vector<Token> _to) : from(_from), to(_to) {}

	/** {@inheritdoc} */
	bool SimpleProduction::apply(tList& list, tList::iterator _position)
	{
		if ((*_position) == this->from)
		{
			list.insert(_position, this->to.begin(), this->to.end());
			return true;
		}

		return false;
	}
}