#pragma once

#include "node.h"

class MCTS
{
	private:

		long iteration;

		std::unique_ptr<Node> root;

		Node* Select();

		Node* Expand(Node* node);

		void BackPropagate(Node* node, SIDE winner, int sc);

	public:

		MOVE Go(Board board, int depth);

		MCTS();

		~MCTS();

};