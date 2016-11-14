#pragma once

#include <list>
#include <memory>
#include <vector>

#include "./language/Token.h"
#include "./production/Production.h"

namespace lsystem
{
	/** 
	 * This class represent an L-System. It contains all productions for the system and knows how to apply them. 
	 * Removal of productions is currently not allowed, since there is no forseeable need to be able to remove any.
	 */
	class LSystem
	{
		private:
			using PVec = std::vector<std::unique_ptr<Production>>;
			using TList = std::list<Token>;

			// The set of productions that identify this L-System.
			PVec productions = PVec();
			
			// The recursion parameter for this L-System.
			unsigned int recursion = 0;

		public:
			/** A simple constructor. */
			LSystem();

			/** A simple destructor. */
			~LSystem();

			/** A copy constructor taking the productions into account. */
			LSystem(const LSystem&);

			/** Applies all productions to the list of tokens. */
			void apply(TList&);

			/** Sets the recursion parameter for this L-System. */
			void setRecursion(unsigned int);

			/** Returns the recursion parameter for this L-System. */
			unsigned int getRecursion();

			/** Returns all productions in this LSystem. */
			std::vector<Production*> getProductions();

			/** Adds a production to this LSystem. */
			void addProduction(Production* const);
	};
}