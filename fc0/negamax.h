#pragma once

#include "board.h"

class Negamax
{
	private:

		long nodes = 0;

		double Quiescence(Board board, double alpha, double beta);

		double NMax(Board board, int depth, double alpha, double beta, std::vector<MOVE>& pv, bool nullMove);

	public:

		MOVE Go(Board board, int depth);
};