#pragma once

#include "board.h"

class Negamax
{
	private:

		long nodes = 0;

		int Quiescence(Board board, int alpha, int beta);

		int NMax(Board board, int depth, int alpha, int beta, std::vector<MOVE>& pv, bool nullMove);

	public:

		MOVE Go(Board board, int depth);
};