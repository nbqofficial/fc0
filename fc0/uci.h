#pragma once

#include "search.h"
#include "perft.h"
#include "training.h"

class UCI
{
	private:

		Perft perft;
		Training training;
		Search search;
		Board board;

	public:

		void Go(char* lineIn);

		void Position(char* lineIn);

		void UciLoop();

};