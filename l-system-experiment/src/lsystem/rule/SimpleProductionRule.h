#pragma once

#include "./ProductionRule.h"

namespace lsystem
{
	template <class A>
	class SimpleProductionRule : public ProductionRule<A>
	{
		private:
			A to;
			A from;

		public:
			SimpleProductionRule(A _from, std::vector<A> _to);
	};
}