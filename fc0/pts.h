#pragma once

#include "board.h"

class PTS
{
	private:

		long nodes = 0;

		int Quiescence(Board board, int alpha, int beta);

		int NegaPTS(Board board, double probability, int alpha, int beta, std::vector<MOVE>& pv);

	public:

		MOVE Go(Board board, double probability);
};