#pragma once

#include "node.h"

class MCTS
{
	private:

		std::unique_ptr<Node> root;

		Node* Select();

		Node* Expand(Node* node);

		void BackPropagate(Node* node, SIDE winner);

	public:

		MOVE Go(Board board);

		MCTS();

		~MCTS();

};