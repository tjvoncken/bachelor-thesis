#include "./Token.h"

namespace lsystem
{
	bool operator==(const Token& _l, const Token& _r)
	{
		return (char) _l == (char) _r;
	}
}