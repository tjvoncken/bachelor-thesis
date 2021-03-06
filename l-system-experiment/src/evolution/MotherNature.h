#pragma once

#include <memory>
#include <random>
#include <vector>
#include <utility>
#include <assert.h>
#include <functional>

#include "./RandomProvider.h"

namespace evolution
{
	/**
	 * This class manages the main process of evolution.
	 * It keeps track of a population at every step, then uses the given fitness and breeding functions to breed the top N pairs with each other.
	 */
	template <class T>
	class MotherNature
	{
		private:
			using PMem = std::pair<std::unique_ptr<T>, unsigned int>;

			using breedFn = std::function<T* (RandomProvider&, const T*, const T*)>;
			using fitnessFn = std::function<unsigned int (T*)>;

			RandomProvider quantum;

			// The current population of T.
			// The fitness of each member is calculated as soon as it enters the population.
			// This should save on repeated fitness calculations.
			std::vector<PMem> population;
			breedFn breedFunction;
			fitnessFn fitnessFunction;

		public:
			/** Creates a new instance of Nature with the given fitness and breed functions. */
			MotherNature(breedFn, fitnessFn);

			/** Sets the population of the world. */
			void setPopulation(const std::vector<T*>&);

			/** 
			 * Breeds the top N of the current generation. If N is not set, the entire population will be bred. If N is 0, nothing will happen.
			 * The old population will be discarded, and a new population will be bred to match the size of the old one.
			 */
			void evolve();
			void evolve(unsigned int, unsigned int);

			/** Get the top N members of the current population according to the given fitness function. */
			std::vector<std::pair<T*, unsigned int>> getTop(unsigned int = 1);
	};

	/** {@inheritdoc} */
	template <class T>
	MotherNature<T>::MotherNature(breedFn _bFn, fitnessFn _fFn) : quantum(), population(), breedFunction(_bFn), fitnessFunction(_fFn) {}

	/** {@inheritdoc} */
	template <class T>
	void MotherNature<T>::setPopulation(const std::vector<T*>& _population)
	{
		// Clear out the current population. The autoptrs should take care of the memory leaks.
		this->population = std::vector<PMem>();

		for(auto member : _population)
		{
			// Calculate the fitness for this new member.
			auto fitness = this->fitnessFunction(member);

			// Walk through the population until we find the proper position to insert this new member.
			auto pos = this->population.begin();
			while (pos != this->population.end() && fitness < pos->second) { pos++; }

			// Insert the new member at the correct position.
			this->population.insert(pos, PMem(std::unique_ptr<T>(member), fitness));
		}
	}

	/** {@inheritdoc} */
	template <class T>
	void MotherNature<T>::evolve() { this->evolve(this->population.size() - 25, 25); }

	/** {@inheritdoc} */
	template <class T>
	void MotherNature<T>::evolve(unsigned int _baseFertile, unsigned int _extraFertile)
	{
		assert(_baseFertile + _extraFertile == this->population.size());

		// 0. Pick with or without replacing? -- Picking with replacing for now because that makes it easier if pop size is odd.

		// 1. Get the size of the current population.
		auto popSize = this->population.size();

		// 2. Get the top N of the current population.
		auto breedingTop = this->getTop(_baseFertile);
		auto dist = this->quantum.getRandomDistribution(0, breedingTop.size() - 1);

		// 5. Repeat from 3 until the new population has the size of the old one.
		auto newPop = std::vector<T*>();
		while(newPop.size() < _baseFertile)
		{
			// 3. Pick 2 with replacing out of the current population.
			auto m1 = breedingTop.at(dist()).first;
			auto m2 = breedingTop.at(dist()).first;

			// 4. Breed the picked 2, insert the new member into the new population.
			newPop.push_back(this->breedFunction(this->quantum, m1, m2));
		}

		// 2. Get the top N of the current population.
		auto extraFertileTop = this->getTop(_extraFertile);
		auto extraDist = this->quantum.getRandomDistribution(0, extraFertileTop.size() - 1);

		// 5. Repeat from 3 until the new population has the size of the old one.
		while (newPop.size() < popSize)
		{
			// 3. Pick 2 with replacing out of the current population.
			auto m1 = extraFertileTop.at(extraDist()).first;
			auto m2 = extraFertileTop.at(extraDist()).first;

			// 4. Breed the picked 2, insert the new member into the new population.
			newPop.push_back(this->breedFunction(this->quantum, m1, m2));
		}

		// 6. Set the new population over the old one.
		this->setPopulation(newPop);
	}

	/** {@inheritdoc} */
	template <class T>
	std::vector<std::pair<T*, unsigned int>> MotherNature<T>::getTop(unsigned int _n)
	{
		auto out = std::vector<std::pair<T*, unsigned int>>();

		unsigned int i;
		std::vector<PMem>::iterator it;
		for (it = this->population.begin(), i = 0; it != this->population.end() && i < _n; it++, i++)
		{
			out.push_back(std::pair<T*, unsigned int>(it->first.get(), it->second));
		}

		return out;
	}
}