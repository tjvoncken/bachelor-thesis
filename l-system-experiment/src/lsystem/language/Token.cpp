#include "./Token.h"

namespace lsystem
{
	/** {@inheritdoc} */
	Token::Token(char _value) : value(_value) {};

	/** {@inheritdoc} */
	Token::operator char() const { return this->value; }

	/** {@inheritdoc} */
	bool operator==(const Token& _l, const Token& _r)
	{
		return (char) _l == (char) _r;
	}
}