#pragma once

#include "board.h"

class Perft
{
	private:

		long leafNodes = 0;

	public:

		void LeafNodeCheck(Board board, int depth);

		void MoveGenSpeedCheck(Board board);

		void Check(Board board, int depth);

};