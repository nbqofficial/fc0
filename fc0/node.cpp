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

SIDE Node::Simulate(int depth)
{
	int baseScore = this->board.EvaluateInt();

	Board temp = this->board;

	for (int i = 0; i < depth; ++i)
	{
		std::vector<MOVE> moves;
		temp.GenerateMoves(moves, GEN_ALL, false);
		if (moves.size() == 0)
		{
			if (temp.IsInCheck(SIDE_WHITE))
			{
				return SIDE_BLACK;
			}
			else if (temp.IsInCheck(SIDE_BLACK))
			{
				return SIDE_WHITE;
			}
			else
			{
				return SIDE_NONE;
			}
		}
		std::random_shuffle(moves.begin(), moves.end(), RandomFunc);
		temp.MakeMove(moves[0]);
	}

	int score = temp.EvaluateInt();

	if (abs(score) > (abs(baseScore) + MCTS_WIN_FACTOR))
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

void Node::Update(SIDE winner)
{
	played += 10;
	SIDE prevSide = SIDE_WHITE;
	if (this->board.GetSide() == SIDE_WHITE)
	{
		prevSide = SIDE_BLACK;
	}
	if (winner == prevSide)
	{
		this->wins += 10;
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

MOVE Node::GetMostWonMove()
{
	auto best = std::max_element(this->children.begin(), this->children.end(),
		[](const std::unique_ptr<Node>& left, const std::unique_ptr<Node>& right) {
			return left->wins < right->wins;
		});

	int bestIndex = std::distance(this->children.begin(), best);

	return this->allowedMoves[bestIndex];
}

MOVE Node::GetBestRatioMove()
{
	double bestRatio = -INF_SCORE;
	int bestIndex = 0;
	for (int i = 0; i < this->children.size(); ++i)
	{
		float p = (this->children[i]->GetRealWins() * 100.0) / this->children[i]->GetRealPlayed();
		if (p >= bestRatio)
		{
			bestRatio = p;
			bestIndex = i;
		}
	}
	return this->allowedMoves[bestIndex];
}

void Node::DisplayMoveProbabilities()
{
	for (int i = 0; i < this->children.size(); ++i)
	{
		float p = (this->children[i]->GetRealWins() * 100.0) / this->children[i]->GetRealPlayed();
		printf("%s | %.2f\n", this->board.MoveToString(allowedMoves[i]).c_str(), p);
	}
}

int Node::GetRealPlayed()
{
	return this->played / 10;
}

int Node::GetRealWins()
{
	return this->wins / 10;
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