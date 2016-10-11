#include "./RewriteEngine.h"

namespace lsystem
{
	/** {@inheritdoc} */
	RewriteEngine::RewriteEngine() : productions() {}

	/** {@inheritdoc} */
	pVec::iterator RewriteEngine::addProduction(Production* _production)
	{
		return this->productions.insert(this->productions.end(), _production);
	}

	/** {@inheritdoc} */
	void RewriteEngine::removeProduction(pVec::iterator _production)
	{
		this->productions.erase(_production); 
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