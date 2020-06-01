#include "valuenet.h"

double ValueNet::Evaluate(Board board, bool isTraining, std::vector<double> outcome)
{
	return this->vn.Evaluate(board.ToTensor(), isTraining, outcome).GetValue(0, 0);
}

double ValueNet::GetError()
{
	return this->vn.GetTotalLoss();
}

ValueNet::ValueNet()
{
	//this->vn.Setup("value.json");
}

ValueNet::~ValueNet()
{
	vn.SaveWeights();
	printf("Value network destructor\n");
}
