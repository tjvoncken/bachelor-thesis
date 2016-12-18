#include "./simpleBreedTokens.h"

#include <set>
#include <list>
#include <random>

namespace evolution
{
	/** {@inheritdoc} */
	TVec* simpleBreedTokens(RandomProvider& _random, const TVec* _a, const TVec* _b)
	{
		auto tokens = new TVec({});
		auto die = _random.getRandomDistribution(1, 2);

		// Insert all tokens from a, when overlapping b, do a 50-50.
		for(unsigned int i = 0; i < _a->size(); i++)
		{
			if(i < _b->size() && die() == 1) { tokens->insert(tokens->end(), lsystem::Token(_b->at(i))); }
			else { tokens->insert(tokens->end(), lsystem::Token(_a->at(i))); }
		}

		// Insert remaining from b, if any.
		for(unsigned int i = _a->size(); i < _b->size(); i++)
		{
			tokens->insert(tokens->end(), lsystem::Token(_b->at(i)));
		}

		// Mutate random tokens. (Duplicate, delete, or randomly change.)
		auto mutDie = _random.getRandomDistribution(1, 100);
		auto it = tokens->begin();
		while(it != tokens->end())
		{
			auto mutRoll = mutDie();

			//10% chance for duplication.
			if (mutRoll > 70 && mutRoll <= 80)
			{ 
				it = tokens->insert(it, lsystem::Token(*it)); 
				it += 2; 
			}
			//10% chance for deletion, but only if it isn't the last one.
			else if(mutRoll > 80 && mutRoll <= 90)
			{
				if(tokens->size() > 1)
				{
					it = tokens->erase(it);
				}
			}
			//10% chance for change.
			else if(mutRoll > 90 && mutRoll <= 100)
			{
				auto tokenDie = _random.getRandomDistribution(65, 80);
				auto tokenRoll = tokenDie();
				while(tokenRoll == 'E') { tokenRoll = tokenDie(); }

				if(tokenRoll == 79) { it = tokens->insert(it, lsystem::Token('[')); }
				else if(tokenRoll == 80) { it = tokens->insert(it, lsystem::Token(']')); }
				else { it = tokens->insert(it, lsystem::Token((char) tokenRoll)); }

				it = tokens->erase(++it);
			}
			else
			{
				it++;
			}
		}

		return tokens;
	};
}