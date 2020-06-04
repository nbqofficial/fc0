#include "mcts.h"

Node* MCTS::Select()
{
	Node* currentNode = this->root.get();

	while (currentNode->IsFullyExpanded() && !currentNode->IsLeaf())
	{
		currentNode = currentNode->GetBestChildren();
	}

	return currentNode;
}

Node* MCTS::Expand(Node* node)
{
	return node->Expand();
}

void MCTS::BackPropagate(Node* node, SIDE winner)
{
	Node* currentNode = node;

	while (currentNode != nullptr)
	{
		currentNode->Update(winner);
		currentNode = currentNode->GetParent();
	}
}

MOVE MCTS::Go(Board board, int depth)
{
	this->root = std::make_unique<Node>(board);

	while (!searchInfo.stopped)
	{
		this->iteration++;
		Node* bestNode = Select();
		Node* expanded = bestNode->Expand();
		SIDE simulationWinner = expanded->Simulate(depth);
		BackPropagate(expanded, simulationWinner);
		CheckUp();
	}
	//printf("Iterations: %ld\n", this->iteration);
	//this->root->DisplayMoveProbabilities();
	MOVE bestMove = root->GetBestRatioMove();
	ClearSearchInfo();
	this->iteration = 0;
	return bestMove;
}

MCTS::MCTS()
{
}

MCTS::~MCTS()
{
}