#pragma once

namespace lsystem
{
	class Token
	{
		public:
			virtual operator char() const = 0;
	};

	/** Default operator== implementation for Token classes. */
	bool operator==(const Token& _l, const Token& _r);
}