#pragma once

namespace lsystem
{
	/** This class represents a basic token. It is just a thinly wrapped char. */
	class Token
	{
		private:
			/** The char representation of this token. */
			char value;

		public:
			/** Token constructor. */
			Token(char _value);

			/** Token to char casting function. */
			virtual operator char() const;
	};

	/** Default operator== implementation for Token classes, just compares their char values. */
	bool operator==(const Token& _l, const Token& _r);
}