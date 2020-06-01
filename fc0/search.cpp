#include "search.h"

MOVE Search::SearchPosition(Board board, int depth, double probability, SEARCH_METHOD method)
{
	MOVE m = { 0 };
	switch (method)
	{
		case METHOD_NEGAMAX:
			m = this->negamax.Go(board, depth);
			break;
		case METHOD_PTS:
			m = this->pts.Go(board, probability);
			break;
		case METHOD_MCTS:
			m = this->mcts.Go(board, MCTS_DEPTH);
			break;
		default:
			m = this->negamax.Go(board, depth);
			break;
	}
	return m;
}
