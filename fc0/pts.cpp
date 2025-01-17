#include "pts.h"

int PTS::Quiescence(Board board, int alpha, int beta)
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

int PTS::NegaPTS(Board board, double probability, int alpha, int beta, std::vector<MOVE>& pv)
{
	if (probability < PROBABILITY_LIMIT) { return Quiescence(board, alpha, beta); }

	if ((nodes & 2047) == 0) { CheckUp(); }

	bool inchk = board.IsInCheck(board.GetSide());

	int score = -INF_SCORE;

	Board b = board;
	std::vector<MOVE> moves;
	board.GenerateMoves(moves, GEN_ALL, true);
	int movesSize = moves.size();

	if (movesSize == 0)
	{
		if (inchk)
		{
			return -MATE_SCORE - probability;
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
		score = -NegaPTS(board, (probability / movesSize), -beta, -alpha, childpv);
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

MOVE PTS::Go(Board board, double probability)
{
	MOVE bestMove = { 0 };
	int bestScore = -INF_SCORE;

	for (double currProb = (PROBABILITY_LIMIT * 10); currProb <= probability; currProb*=10)
	{
		std::vector<MOVE> newpv;
		bestScore = NegaPTS(board, currProb, -INF_SCORE, INF_SCORE, newpv);
		if (searchInfo.stopped)
		{
			break;
		}
		bestMove = newpv[0];
		//printf("info score cp %d depth %f nodes %ld ", (int)bestScore, currProb, this->nodes);
		//printf("info nodes %ld\n", this->nodes);
		//board.DisplayPv(newpv);
		//printf("Move ordering: %.2f\n", (searchInfo.fhf / searchInfo.fh));
		//printf("Null cuttoffs: %d\n", searchInfo.nullCutoff);
	}
	ClearSearchInfo();
	this->nodes = 0;
	return bestMove;
}
