#pragma once

#include "board.h"

class Node
{
	private:

		Board board;
		Node* parent = nullptr;
		std::vector<MOVE> allowedMoves;
		std::vector<std::unique_ptr<Node>> children;
		int played = 0;
		int wins = 0;

	public:

		bool IsFullyExpanded();

		bool IsLeaf();

		bool HasParent();

		double GetUCT();

		Node* GetParent();

		Node* GetBestChildren();

		Node* Expand();

		SIDE Simulate();

		void Update(SIDE winner);

		MOVE GetMostVisitedMove();

		int GetRealPlayed();

		Node(Board board);

		Node(Board board, MOVE move, Node* parent);

		~Node();

};