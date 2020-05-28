#pragma once

#include "negamax.h"
#include "pts.h"

class Search
{
	private:

		Negamax negamax;
		PTS pts;

	public:

		MOVE SearchPosition(Board board, int depth, double probability, SEARCH_METHOD method);

};