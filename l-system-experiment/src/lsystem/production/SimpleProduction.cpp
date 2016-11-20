#include "./SimpleProduction.h"

namespace lsystem
{
	/** {@inheritdoc} */
	SimpleProduction::~SimpleProduction() {};

	/** {@inheritdoc} */
	SimpleProduction* SimpleProduction::clone() const { return new SimpleProduction(*this); }

	/** {@inheritdoc} */
	std::vector<Token> SimpleProduction::getTo() const { return this->to; }

	/** {@inheritdoc} */
	SimpleProduction::SimpleProduction(Token _from, std::vector<Token> _to) : Production(_from), to(_to) {}

	/** {@inheritdoc} */
	bool SimpleProduction::apply(TList& list, TList::iterator _position)
	{
		if((*_position) == this->from)
		{
			list.insert(_position, this->to.begin(), this->to.end());
			return true;
		}

		return false;
	}
}