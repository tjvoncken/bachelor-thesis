#include "./distanceFitnessSystem.h"

#include <map>
#include <list>
#include <vector>
#include <assert.h>
#include <algorithm>

#include "../../../graph/Edge.h"
#include "../../../graph/Graph.h"
#include "../../../graph/Vertex.h"

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

			return distanceFitness(string, system->getRecursion() + system->getProductions().size());
		};
	}
}