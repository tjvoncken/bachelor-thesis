#include "./LSystem.h"

namespace lsystem
{
	/** {@inheritdoc} */
	LSystem::LSystem() {}

	/** {@inheritdoc} */
	LSystem::~LSystem() {}

	/** {@inheritdoc} */
	LSystem::LSystem(const LSystem& _original)
	{
		// Copy the recursion parameter from the previous L-System.
		this->recursion = _original.recursion;

		// Copy all production from the previous L-System.
		this->productions = PMap();
		for(auto it = _original.productions.begin(); it != _original.productions.end(); it++)
		{
			auto prod = it->second.get()->clone();
			this->productions.insert(PMap::value_type(prod->getFrom(), std::unique_ptr<Production>(prod)));
		}
	}

	/** {@inheritdoc} */
	void LSystem::apply(TList& _string)
	{
		for(unsigned int i = 0; i < this->recursion; i++)
		{
			auto it = _string.begin();
			while(it != _string.end())
			{
				auto pIt = this->productions.find(*it);
				if(pIt != this->productions.end())
				{
					pIt->second->apply(_string, it);
					it = _string.erase(it);
				}
				else
				{
					it++;
				}
			}
		}
	}

	/** {@inheritdoc} */
	void LSystem::setRecursion(unsigned int _recursion) { this->recursion = _recursion; }

	/** {@inheritdoc} */
	unsigned int LSystem::getRecursion() const { return this->recursion; }

	/** {@inheritdoc} */
	std::vector<Production*> LSystem::getProductions() const
	{ 
		auto out = std::vector<Production*>();
		for(auto it = this->productions.begin(); it != this->productions.end(); it++) { out.push_back(it->second.get()); }
		return out;
	}

	/** {@inheritdoc} */
	void LSystem::addProduction(Production* const _p)
	{
		auto pIt = this->productions.find(_p->getFrom());
		if(pIt == this->productions.end())
		{
			this->productions.insert(PMap::value_type(_p->getFrom(), std::unique_ptr<Production>(_p)));
		}
		else
		{
			pIt->second = std::unique_ptr<Production>(_p);
		}
	}
}