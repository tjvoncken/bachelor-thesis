#include "./RandomProvider.h"

#include <assert.h>

namespace evolution
{
	/** {@inheritdoc} */
	RandomProvider::RandomProvider() : randomGenerator() {}

	/** {@inheritdoc} */
	RandomProvider::~RandomProvider() 
	{
		// Delete all distributions.
		for(auto it = this->distributions.begin(); it != this->distributions.end(); it++) { delete it->second; }
	}

	/** {@inheritdoc} */
	std::function<int ()> RandomProvider::getRandomDistribution(int _min, int _max)
	{
		auto key = std::pair<int, int>(_min, _max);

		// Get (and create if necessary) the distribution from min to max.
		std::uniform_int_distribution<int>* dist;

		if(this->distributions.count(key) <= 0)
		{ 
			auto result = this->distributions.insert(DistMap::value_type(key, new std::uniform_int_distribution<int>(_min, _max)));
			dist = result.first->second; 
		}
		else { dist = this->distributions.find(key)->second; }

		// Return a function wrapping it.
		return [&, dist]() { return (*dist)(this->randomGenerator);  };
	}

	/** {@inheritdoc} */
	bool RandomProvider::trueWithChance(double _chance)
	{
		assert(_chance >= 0 && _chance <= 1);

		//TODO
		return false;
	}
}