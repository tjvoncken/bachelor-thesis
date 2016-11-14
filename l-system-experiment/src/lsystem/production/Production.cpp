#include "./Production.h"

namespace lsystem
{
	/** {@inheritdoc} */
	Production::~Production() {};

	/** {@inheritdoc} */
	Production* Production::clone() const { return new Production(*this); }

	/** {@inheritdoc} */
	bool Production::apply(TList& list, TList::iterator _position) { return false; }
}