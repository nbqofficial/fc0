#pragma once

#include "board.h"

class PTS
{
	private:

		long nodes = 0;

		double Quiescence(Board board, double alpha, double beta);

		double NegaPTS(Board board, double probability, double alpha, double beta, std::vector<MOVE>& pv, bool nullMove);

	public:

		MOVE Go(Board board, double probability);
};