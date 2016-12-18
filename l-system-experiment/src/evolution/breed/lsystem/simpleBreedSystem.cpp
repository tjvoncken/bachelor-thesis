#include "./simpleBreedSystem.h"

#include <set>
#include <random>

#include "../../../lsystem/production/SimpleProduction.h"

namespace evolution
{
	void breedRecursion(RandomProvider& _random, lsystem::LSystem* _target, const lsystem::LSystem* _a, const lsystem::LSystem* _b);
	void breedProductions(RandomProvider& _random, lsystem::LSystem* _target, const lsystem::LSystem* _a, const lsystem::LSystem* _b);

	/** {@inheritdoc} */
	lsystem::LSystem* simpleBreedSystem(RandomProvider& random, const lsystem::LSystem* _a, const lsystem::LSystem* _b)
	{
		auto system = new lsystem::LSystem();

		// Breed and mutate the recursion param.
		breedRecursion(random, system, _a, _b);

		// Breed and mutate the productions.
		breedProductions(random, system, _a, _b);

		return system;
	};

	void breedRecursion(RandomProvider& _random, lsystem::LSystem* _target, const lsystem::LSystem* _a, const lsystem::LSystem* _b)
	{
		// Average the recursion params.
		_target->setRecursion((_a->getRecursion() + _b->getRecursion()) / 2);

		// Roll a virtual die.
		auto dist = _random.getRandomDistribution(1, 6);
		auto roll = dist(); // Dice roll :D

							// Do -1 if the roll was 1, +1 if was 6, nothing otherwise.
		if (roll == 1 && _target->getRecursion() > 1) { _target->setRecursion(_target->getRecursion() - 1); }
		else if (roll == 6) { _target->setRecursion(_target->getRecursion() + 1); }
	}

	using ProductionMap = std::map<lsystem::Token, lsystem::SimpleProduction*>;
	void mapSimpleProductions(RandomProvider&, ProductionMap&, lsystem::LSystem*, const lsystem::LSystem*);

	void breedProductions(RandomProvider& _random, lsystem::LSystem* _target, const lsystem::LSystem* _a, const lsystem::LSystem* _b)
	{
		auto simpleProductions = ProductionMap();

		// Loop through all productions from system _a.
		mapSimpleProductions(_random, simpleProductions, _target, _a);

		// Loop through all productions from system _b.
		mapSimpleProductions(_random, simpleProductions, _target, _b);

		// Build a map of all valid tokens to be inserted into the productions.
		// This is an optimization, which should greatly reduce non-sense tokens.
		// Which should speed up interpretation of the string.
		std::set<char> validTokens = std::set<char>({ 'R', 'L', 'F', 'B' });
		for(auto it = simpleProductions.begin(); it != simpleProductions.end(); it++) { validTokens.insert(it->first); }

		// Mutate the relevant productions.
		// TODO: try possible optimization by not creating a production for every token, but creating them randomly. 
		// TODO: (this should reduce the impact of garbage tokens by a large margin, and also open the system up for more mutation (better against local minima).)
		auto die = _random.getRandomDistribution(1, 100);
		auto it = simpleProductions.begin();
		while (it != simpleProductions.end())
		{
			// Roll a die.
			auto actionRoll = die();

			// 60% chance of not mutating at all.
			if (actionRoll <= 60)
			{
				// Do nothing in most cases, except duplicating the production.
				it->second = it->second->clone();
			}
			else
			{
				// Add or remove a token from the "to" side of the production at random.
				// If a previously unknown token was added, add an identity production for that token to the system.
				auto production = it->second;
				auto to = production->getTo();
				auto from = production->getFrom();

				if (actionRoll > 60 && actionRoll <= 74)
				{
					if (to.size() > 1)
					{
						// Remove a token if there are more than 1.
						auto die = _random.getRandomDistribution(0, to.size() - 1);
						to.erase(to.begin() + die());

						// Re-insert new production.
						it->second = new lsystem::SimpleProduction(production->getFrom(), to);
					}
					else
					{
						// Simply clone the production if there was into 1 "to" token.
						it->second = it->second->clone();
					}
				}
				else if (actionRoll > 74 && actionRoll <= 88)
				{
					// Add a token.

					// Generate random char from A to Z and insert it randomly into the "to" token list.
					// But make sure to not generate an S or an E, and leave those tokens alone.
					auto alphabet = _random.getRandomDistribution(0, validTokens.size() - 1); //A-Z = 65-90
					char c = *(std::next(validTokens.begin(), alphabet()));

					auto cToken = lsystem::Token(c);

					auto die = _random.getRandomDistribution(0, to.size() - 1);
					to.insert(to.begin() + die(), cToken);

					// Re-insert new production(s)...
					it->second = new lsystem::SimpleProduction(production->getFrom(), to);
				}
				else if (actionRoll > 88 && actionRoll <= 96)
				{
					// Convert the current production into a branch.
					to.insert(to.begin(), lsystem::Token('['));
					to.insert(to.end(), lsystem::Token(']'));

					// Re-insert new production.
					it->second = new lsystem::SimpleProduction(production->getFrom(), to);
				}
				else if (actionRoll > 96)
				{
					// Remove the production entirely.
					it = simpleProductions.erase(it);
				}
			}

			// Increment pointer if we didn't delete the current one.
			if (actionRoll <= 96) { it++; }
		}

		// 30% chance to spawn a random production from a random Token to 'F'.
		// If the chose production already exists, do nothing.
		auto bonusRoll = die();
		if (bonusRoll > 70)
		{
			// Make sure not to generate productions transforming the 'S' or 'E' token.
			auto alphabet = _random.getRandomDistribution(65, 78); //A-Z = 65-90
			char c = alphabet();
			while (c == 'S' || c == 'E') { c = alphabet(); }

			auto token = lsystem::Token(c);

			auto p = new lsystem::SimpleProduction(token, std::vector<lsystem::Token>({ lsystem::Token('F') }));
			auto r = simpleProductions.insert(ProductionMap::value_type(token, p));
			if (r.second == false) { delete p; }
		}

		// Insert production into _target.
		for (auto it = simpleProductions.begin(); it != simpleProductions.end(); it++)
		{
			_target->addProduction(it->second);
		}
	}

	void mapSimpleProductions(RandomProvider& _random, ProductionMap& _productions, lsystem::LSystem* _target, const lsystem::LSystem* _origin)
	{
		// Loop through all productions from system _b.
		auto productions = _origin->getProductions();
		for (auto it = productions.begin(); it != productions.end(); it++)
		{
			// See if the production is simple.
			auto simpleProduction = dynamic_cast<lsystem::SimpleProduction*>(*it);
			if (simpleProduction != NULL)
			{
				// See if the production already exists, if not simply insert this one into the map, if it does, insert one of the two at random into the map.
				auto mapIt = _productions.find(simpleProduction->getFrom());
				if (mapIt != _productions.end())
				{
					auto dist = _random.getRandomDistribution(1, 2);
					if (dist() == 2) { mapIt->second = simpleProduction; }
				}
				else
				{
					_productions.insert(ProductionMap::value_type(simpleProduction->getFrom(), simpleProduction));
				}
			}
			// We cannot currently handle these productions, so copy them directly into the system.
			else { _target->addProduction((*it)->clone()); }
		}
	}
}