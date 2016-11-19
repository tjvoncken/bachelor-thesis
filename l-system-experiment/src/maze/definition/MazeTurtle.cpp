#include "./MazeTurtle.h"

#include <algorithm>
#include <stdexcept>
#include "./Language.h"

namespace maze
{
	/** {@inheritdoc} */
	MazeTurtle::MazeTurtle() : tokenFns(), stack(), state()
	{
		// Register the default turtle functions.
		auto fwFn = [&](const lsystem::Token&, const TurtleState& oState, const TurtleState& nState) { return TurtleState(nState.position + nState.heading, nState.heading); };
		this->registerTokenFn(lsystem::Token(Language::T_FORWARD), fwFn);

		auto bwFn = [&](const lsystem::Token&, const TurtleState& oState, const TurtleState& nState) { return TurtleState(nState.position + (-1 * nState.heading), nState.heading); };
		this->registerTokenFn(lsystem::Token(Language::T_BACKWARD), bwFn);

		auto lFn = [&](const lsystem::Token&, const TurtleState& oState, const TurtleState& nState) { return TurtleState(nState.position, nState.heading.rotate(90)); };
		this->registerTokenFn(lsystem::Token(Language::T_LEFT), lFn);

		auto rFn = [&](const lsystem::Token&, const TurtleState& oState, const TurtleState& nState) { return TurtleState(nState.position, nState.heading.rotate(-90)); };
		this->registerTokenFn(lsystem::Token(Language::T_RIGHT), rFn);

		auto pushFn = [&](const lsystem::Token&, const TurtleState& oState, const TurtleState& nState) { this->stack.push_back(oState); return nState; };
		this->registerTokenFn(lsystem::Token(Language::T_PUSH), pushFn);
		this->registerTokenFn
		(
			lsystem::Token(Language::T_POP), 
			[&](const lsystem::Token&, const TurtleState& oState, const TurtleState& nState)
			{ 
				if (this->stack.size() <= 0) { return nState; /* throw std::runtime_error("Cannot POP if there has not been a PUSH."); */ }
				else
				{
					auto nState = this->stack.back();
					this->stack.pop_back();

					return nState;
				}
			}
		);
	}

	/** {@inheritdoc} */
	void MazeTurtle::registerTokenFn(const lsystem::Token token, MazeTurtle::TokenFn fn)
	{
		auto& vec = this->tokenFns[token];
		vec.insert(vec.end(), fn);
	}

	/** {@inheritdoc} */
	coordinates::grid::Point MazeTurtle::getPosition() { return this->state.position; }

	/** {@inheritdoc} */
	coordinates::grid::Vector MazeTurtle::getHeading() { return this->state.heading; }

	/** {@inheritdoc} */
	void MazeTurtle::execute(const lsystem::Token& token)
	{
		if(this->tokenFns.count(token) > 0)
		{
			auto oState = this->state;

			auto fns = this->tokenFns.find(token)->second;
			for(auto fn : fns) { this->state = fn(token, oState, this->state); }
		}
	}
}