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

MOVE MCTS::Go(Board board)
{
	this->root = std::make_unique<Node>(board);

	int start = GetTickCount();

	while (!searchInfo.stopped)
	{
		Node* bestNode = Select();
		Node* expanded = bestNode->Expand();
		SIDE simulationWinnder = expanded->Simulate();
		BackPropagate(expanded, simulationWinnder);
		CheckUp();
	}

	MOVE bestMove = root->GetMostVisitedMove();
	return bestMove;
}

MCTS::MCTS()
{
}

MCTS::~MCTS()
{
}
