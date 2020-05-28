#pragma once

#include "hivemind.h"
#include "board.h"

class ValueNet
{
	private:

		HiveMind vn;

	public:

		double Evaluate(Board board, bool isTraining, std::vector<double> outcome);

		double GetError();

		ValueNet();

		~ValueNet();

};