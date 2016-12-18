#include "./distanceFitnessTokens.h"

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
	unsigned int distanceFitnessTokens(std::vector<lsystem::Token>* _tokens)
	{
		std::list<lsystem::Token> string = std::list<lsystem::Token>(_tokens->begin(), _tokens->end());
		string.insert(string.begin(), lsystem::Token('S'));
		string.insert(string.end(), lsystem::Token('E'));

		distanceFitness(string, 2 * _tokens->size());
	}
}