#pragma once

#include <list>
#include <vector>
#include <functional>

#include "../lsystem/LSystem.h"
#include "../lsystem/language/Token.h"
#include "../evolution/RandomProvider.h"

using LSystem = lsystem::LSystem;
using LSystemBreedFn = std::function<lsystem::LSystem* (evolution::RandomProvider&, const lsystem::LSystem*, const lsystem::LSystem*)>;
using LSystemFitnessFn = std::function<std::function<unsigned int (lsystem::LSystem*)> (const std::list<lsystem::Token>&)>;

/** Runs the test with given name for given generations on L-Systems. */
void runLSystemsTest(std::string _testName, unsigned int _population, unsigned int _generations, unsigned int _dying, LSystemBreedFn _breedFn, LSystemFitnessFn _fitnessFn);

using TokenString = std::vector<lsystem::Token>;
using TokenStringBreedFn = std::function<TokenString* (evolution::RandomProvider&, const TokenString*, const TokenString*)>;
using TokenStringFitnessFn = std::function<unsigned int (TokenString*)>;

/** Runs the test with given name for given generations on a string of tokens. */
void runTokenStringTest(std::string _testName, unsigned int _population, unsigned int _generations, unsigned int _dying, TokenStringBreedFn _breedFn, TokenStringFitnessFn _fitnessFn);