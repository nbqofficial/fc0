#include "node.h"

bool Node::IsFullyExpanded()
{
	return this->children.size() == this->allowedMoves.size();
}

bool Node::IsLeaf()
{
	return this->children.empty();
}

bool Node::HasParent()
{
	return this->parent != nullptr;
}

double Node::GetUCT()
{
	if (!this->played) { return 0.0; }
	return this->wins / (double)this->played + 1.42 * sqrt(log(this->parent->played) / this->played);
}

Node* Node::GetParent()
{
	return this->parent;
}

Node* Node::GetBestChildren()
{
	auto best = std::max_element(this->children.begin(), this->children.end(),
		[](const std::unique_ptr<Node>& left, const std::unique_ptr<Node>& right) {
			return left->GetUCT() < right->GetUCT();
		});

	return best->get();
}

Node* Node::Expand()
{
	if (this->children.size() >= this->allowedMoves.size())
		return this;

	this->children.push_back(std::make_unique<Node>(this->board, this->allowedMoves[this->children.size()], this));
	return this->children.back().get();
}

SIDE Node::Simulate(int depth, int& sc)
{
	Board temp = this->board;

	for (int i = 0; i < depth; ++i)
	{
		std::vector<MOVE> moves;
		temp.GenerateMoves(moves, GEN_ALL, false);
		std::random_shuffle(moves.begin(), moves.end());
		if (moves.size() == 0)
		{
			if (board.IsInCheck(SIDE_WHITE))
			{
				sc = MATE_SCORE;
				return SIDE_BLACK;
			}
			else if (board.IsInCheck(SIDE_BLACK))
			{
				sc = MATE_SCORE;
				return SIDE_WHITE;
			}
			else
			{
				sc = 0;
				return SIDE_NONE;
			}
		}
		else
		{
			temp.MakeMove(moves[0]);
		}
	}

	int score = temp.EvaluateInt();
	sc = abs(score);

	if (abs(score) > MCTS_WIN_FACTOR)
	{
		if (score > 0)
		{
			return SIDE_WHITE;
		}
		else
		{
			return SIDE_BLACK;
		}
	}
	return SIDE_NONE;
}

void Node::Update(SIDE winner, int score)
{
	played += 10;
	SIDE prevSide = SIDE_WHITE;
	if (this->board.GetSide() == SIDE_WHITE)
	{
		prevSide = SIDE_BLACK;
	}
	if (winner == prevSide)
	{
		this->wins += (10 * (score / 1000));
	}
	else if (winner == SIDE_NONE)
	{
		this->wins += 5;
	}
}

MOVE Node::GetMostVisitedMove()
{
	auto best = std::max_element(this->children.begin(), this->children.end(),
		[](const std::unique_ptr<Node>& left, const std::unique_ptr<Node>& right) {
			return left->played < right->played;
		});

	int bestIndex = std::distance(this->children.begin(), best);

	return this->allowedMoves[bestIndex];
}

int Node::GetRealPlayed()
{
	return this->played / 10;
}

Node::Node(Board board)
{
	this->board = board;
	this->board.GenerateMoves(this->allowedMoves, GEN_ALL, false);
}

Node::Node(Board board, MOVE move, Node* parent)
{
	this->board = board;
	this->parent = parent;
	this->board.MakeMove(move);
	this->board.GenerateMoves(this->allowedMoves, GEN_ALL, false);
}

Node::~Node()
{
}