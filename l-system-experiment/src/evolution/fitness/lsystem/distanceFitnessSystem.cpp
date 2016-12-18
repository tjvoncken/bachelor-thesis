#include "./distanceFitnessSystem.h"

#include <map>
#include <list>
#include <vector>
#include <assert.h>
#include <algorithm>

#include "../../../graph/Edge.h"
#include "../../../graph/Graph.h"
#include "../../../graph/Vertex.h"

#include "../../../lsystem/production/SimpleProduction.h"

#include "../../../maze/representation/graph/GraphBuilder.h"
#include "../../../maze/representation/graph/helper/MazeGraph.h"

#include "../common/distanceFitness.h"

namespace evolution
{
	/** {@inheritdoc} */
	std::function<unsigned int (lsystem::LSystem*)> distanceFitnessSystem(const std::list<lsystem::Token>& input)
	{
		return [&](lsystem::LSystem* system) -> unsigned int
		{
			auto string = std::list <lsystem::Token>(input);
			system->apply(string);

			auto productions = system->getProductions();
			auto maxLength = 0;
			for(auto production : productions)
			{
				auto simple = dynamic_cast<lsystem::SimpleProduction*>(production);
				if(simple->getTo().size() > maxLength) { maxLength = simple->getTo().size(); }
			}

			return distanceFitness(string, system->getRecursion() + maxLength);
		};
	}
}