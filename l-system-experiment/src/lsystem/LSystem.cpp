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
		this->productions = PVec();
		for(auto it = _original.productions.begin(); it != _original.productions.end(); it++)
		{
			this->productions.push_back(std::unique_ptr<Production>(it->get()->clone()));
		}
	}

	/** {@inheritdoc} */
	void LSystem::apply(TList& _string)
	{
		for(unsigned int i = 0; i < this->recursion; i++)
		{
			auto it = _string.begin();
			while (it != _string.end())
			{
				bool productionApplied = false;
				for (auto pIt = this->productions.begin(); pIt != this->productions.end(); pIt++)
				{
					productionApplied = productionApplied || (*pIt)->apply(_string, it);
				}

				if (productionApplied) { it = _string.erase(it); }
				else { it++; }
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
		for(auto it = this->productions.begin(); it != this->productions.end(); it++) { out.push_back(it->get()); }
		return out;
	}

	/** {@inheritdoc} */
	void LSystem::addProduction(Production* const _p)
	{
		this->productions.push_back(std::unique_ptr<Production>(_p));
	}
}