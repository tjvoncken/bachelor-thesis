#include "./RewriteEngine.h"

namespace lsystem
{
	template <typename A>
	RewriteEngine<A>::RewriteEngine() : rules() {}

	template <typename A>
	tList<A> RewriteEngine<A>::rewrite(unsigned int iterations, tIt<A> _start, tIt<A> _end)
	{
		tList<A> buffer = tList<A>();

		if(iterations == 0) { return buffer; }
		else
		{
			for(auto it = buffer.begin(); it != buffer.end(); it = buffer.erase(it))
			{
				for(auto it = this->rules.begin(); it != this->rules.end(); it++)
				{
					it->apply(buffer, it);
				}
			}

			return rewrite(iterations - 1, buffer.begin(), buffer.end());
		}
	}
}