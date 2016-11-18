#pragma once

#include <map>
#include <random>
#include <functional>

namespace evolution
{
	class RandomProvider
	{
		private:
			using DistMap = std::map<std::pair<int, int>, std::uniform_int_distribution<int>*>;

			std::random_device device;
			std::mt19937 randomGenerator;

			DistMap distributions;

		public:
			/** Simple constructor. */
			RandomProvider();

			/** Simple destructor. */
			~RandomProvider();

			/**
			 * Returns a function which return a random number within the given min-max range (including range-borders).
			 * Numbers will be evenly distributed along the range.
			 */
			std::function<int ()> getRandomDistribution(int min, int max);

			/**
			 * Returns true with the given chance, false otherwise.
			 * Chance should be between 0 and 1.
			 */
			bool trueWithChance(double chance);
	};
}