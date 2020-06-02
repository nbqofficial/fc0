#include "pts.h"

double PTS::Quiescence(Board board, double alpha, double beta)
{
	if ((nodes & 2047) == 0) { CheckUp(); }

	this->nodes++;

	double score = board.Evaluate();

	if (score >= beta) { return beta; }

	if (score > alpha) { alpha = score; }

	Board b = board;
	std::vector<MOVE> moves;
	board.GenerateMoves(moves, GEN_VIOLENT, false);
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

double PTS::NegaPTS(Board board, double probability, double alpha, double beta, std::vector<MOVE>& pv, bool nullMove)
{
	if (probability < PROBABILITY_LIMIT) { return Quiescence(board, alpha, beta); }

	if ((nodes & 2047) == 0) { CheckUp(); }

	bool inchk = board.IsInCheck(board.GetSide());
	if (inchk)
	{
		probability *= 10;
	}

	double score = -INF_SCORE;

	if (nullMove && !inchk && searchInfo.probability != probability && probability >= (pow(10.0, (NULL_MOVE_R + 1))))
	{
		std::vector<MOVE> cpv;
		board.SwitchSide();
		score = -NegaPTS(board, (probability / pow(10.0, (NULL_MOVE_R + 1))), -beta, -beta + 1, cpv, false);
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
		score = -NegaPTS(board, (probability / movesSize), -beta, -alpha, childpv, true);
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
	double bestScore = -INF_SCORE;

	for (double currProb = (PROBABILITY_LIMIT * 10); currProb <= probability; currProb*=10)
	{
		std::vector<MOVE> newpv;
		bestScore = NegaPTS(board, currProb, -INF_SCORE, INF_SCORE, newpv, true);
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
