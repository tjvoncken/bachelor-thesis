#include "./RewriteEngine.h"

#include <memory>

namespace lsystem
{
	/** {@inheritdoc} */
	RewriteEngine::RewriteEngine() : productions() {}

	/** {@inheritdoc} */
	RewriteEngine::pVec::iterator RewriteEngine::addProduction(Production* const _production)
	{
		this->productions.push_back(std::unique_ptr<Production>(_production));
		return --this->productions.end();
	}

	/** {@inheritdoc} */
	std::unique_ptr<Production> RewriteEngine::removeProduction(pVec::iterator _production)
	{
		this->productions.erase(_production);
		return std::move(*_production);
	}

	/** {@inheritdoc} */
	tList RewriteEngine::rewrite(unsigned int iterations, tList::iterator _start, tList::iterator _end)
	{
		tList buffer = tList(_start, _end);

		if (iterations == 0) { return buffer; }
		else
		{
			auto it = buffer.begin();
			while (it != buffer.end())
			{
				bool pRan = false;
				for (auto pIt = this->productions.begin(); pIt != this->productions.end(); pIt++)
				{
					pRan = pRan || (*pIt)->apply(buffer, it);
				}

				if (pRan) { it = buffer.erase(it); }
				else { it++; }
			}

			return rewrite(iterations - 1, buffer.begin(), buffer.end());
		}
	}
}