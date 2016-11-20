#include "./Production.h"

namespace lsystem
{
	/** {@inheritdoc} */
	Production::Production(Token _t) : from(_t) {};

	/** {@inheritdoc} */
	Production::Production(const Production& _p) : from(_p.from) {};

	/** {@inheritdoc} */
	Production::~Production() {};

	/** {@inheritdoc} */
	Production* Production::clone() const { return new Production(*this); }

	/** {@inheritdoc} */
	Token Production::getFrom() const { return this->from; }

	/** {@inheritdoc} */
	bool Production::apply(TList& list, TList::iterator _position) { return false; }
}