#pragma once

#include "negamax.h"
#include "pts.h"
#include "mcts.h"

class Search
{
	private:

		Negamax negamax;
		PTS pts;
		MCTS mcts;

	public:

		MOVE SearchPosition(Board board, int depth, double probability, SEARCH_METHOD method);

};