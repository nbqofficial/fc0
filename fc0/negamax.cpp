#include "negamax.h"

int Negamax::Quiescence(Board board, int alpha, int beta)
{
	if ((nodes & 2047) == 0) { CheckUp(); }

	this->nodes++;

	int score = board.EvaluateAll();

	if (score >= beta) { return beta; }

	if (score > alpha) { alpha = score; }

	Board b = board;
	std::vector<MOVE> moves;
	board.GenerateMoves(moves, GEN_VIOLENT, true);
	int movesSize = moves.size();

	score = -INF_SCORE;

	for (int i = 0; i < movesSize; i++)
	{
		board.MakeMove(moves[i]); // make move
		score = -Quiescence(board, -beta, -alpha);
		board = b; // take back move

		if (searchInfo.stopped)
		{
			break;
		}

		if (score > alpha)
		{
			if (score >= beta)
			{
				return beta;
			}
			alpha = score;
		}
	}
	return alpha;
}

int Negamax::NMax(Board board, int depth, int alpha, int beta, std::vector<MOVE>& pv, bool nullMove)
{
	if (depth <= 0) { return Quiescence(board, alpha, beta); }

	if ((nodes & 2047) == 0) { CheckUp(); }

	bool inchk = board.IsInCheck(board.GetSide());

	int score = -INF_SCORE;

	if (nullMove && !inchk && searchInfo.depth != depth && depth >= (NULL_MOVE_R + 1))
	{
		std::vector<MOVE> cpv;
		board.SwitchSide();
		score = -NMax(board, (depth - NULL_MOVE_R - 1), -beta, -beta + 1, cpv, false);
		board.SwitchSide();
		if (score >= beta && abs(alpha) < (MATE_SCORE - MAX_DEPTH))
		{ 
			searchInfo.nullCutoff++;
			return beta; 
		}
	}

	score = -INF_SCORE;

	Board b = board;
	std::vector<MOVE> moves;
	board.GenerateMoves(moves, GEN_ALL, true);
	int movesSize = moves.size();

	if (movesSize == 0)
	{
		if (inchk)
		{
			return -MATE_SCORE + (MAX_DEPTH - depth);
		}
		else
		{
			return 0.0;
		}
	}

	for (int i = 0; i < movesSize; ++i)
	{
		std::vector<MOVE> childpv;
		board.MakeMove(moves[i]); // make move
		score = -NMax(board, depth - 1, -beta, -alpha, childpv, true);
		board = b; // take back move

		if (searchInfo.stopped)
		{
			break;
		}

		if (score > alpha)
		{
			if (score >= beta)
			{
				if (i == 0)
				{
					searchInfo.fhf++;
				}
				searchInfo.fh++;
				return beta;
			}
			alpha = score;
			// set pv
			pv.clear();
			pv.push_back(moves[i]);
			std::copy(childpv.begin(), childpv.end(), std::back_inserter(pv));
		}
	}
	return alpha;
}

MOVE Negamax::Go(Board board, int depth)
{
	MOVE bestMove = { 0 };
	int bestScore = -INF_SCORE;

	for (int currDepth = 1; currDepth <= depth; currDepth++)
	{
		std::vector<MOVE> newpv;
		bestScore = NMax(board, currDepth, -INF_SCORE, INF_SCORE, newpv, true);
		if (searchInfo.stopped)
		{
			break;
		}
		bestMove = newpv[0];
		//printf("info score cp %d depth %d nodes %ld ", (int)(bestScore / 100), currDepth, this->nodes);
		//printf("info depth %d nodes %ld\n", currDepth, this->nodes);
		//board.DisplayPv(newpv);
		//printf("Move ordering: %.2f\n", (searchInfo.fhf / searchInfo.fh));
		//printf("Null cuttoffs: %d\n", searchInfo.nullCutoff);
	}

	ClearSearchInfo();
	this->nodes = 0;
	return bestMove;
}
