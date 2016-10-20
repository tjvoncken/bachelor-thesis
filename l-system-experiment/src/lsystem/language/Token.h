#pragma once

namespace lsystem
{
	/** This class represents a basic token. It is just a thinly wrapped char. */
	class Token
	{
		friend bool operator==(const Token&, const Token&);

		private:
			/** The char representation of this token. */
			char value;

		public:
			/** Token constructor. */
			Token(char value);

			/** Token to char casting function. */
			virtual operator char() const;
	};

	/** Default operator== implementation for Token classes, just compares their char values. */
	bool operator==(const Token& lhs, const Token& rhs);
}