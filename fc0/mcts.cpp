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

void MCTS::BackPropagate(Node* node, SIDE winner, int score)
{
	Node* currentNode = node;

	while (currentNode != nullptr)
	{
		currentNode->Update(winner, score);
		currentNode = currentNode->GetParent();
	}
}

MOVE MCTS::Go(Board board, int depth)
{
	this->root = std::make_unique<Node>(board);

	while (!searchInfo.stopped)
	{
		int score = 0;
		Node* bestNode = Select();
		Node* expanded = bestNode->Expand();
		SIDE simulationWinnder = expanded->Simulate(depth, score);
		//printf("%d\n", score);
		BackPropagate(expanded, simulationWinnder, score);
		CheckUp();
	}

	MOVE bestMove = root->GetMostVisitedMove();
	ClearSearchInfo();
	return bestMove;
}

MCTS::MCTS()
{
}

MCTS::~MCTS()
{
}