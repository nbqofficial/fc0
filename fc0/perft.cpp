#include "perft.h"

void Perft::LeafNodeCheck(Board board, int depth)
{
	if (depth == 0)
	{
		this->leafNodes++;
		return;
	}

	Board b = board;
	std::vector<MOVE> moves;
	board.GenerateMoves(moves, GEN_ALL, false);
	int movesSize = moves.size();

	for (int i = 0; i < movesSize; i++)
	{
		board.MakeMove(moves[i]);
		LeafNodeCheck(board, depth - 1);
		board = b;
	}
	return;
}

void Perft::MoveGenSpeedCheck(Board board)
{
	auto execTime = 0.0;

	auto startTime = std::chrono::high_resolution_clock::now();

	std::vector<MOVE> moves;
	board.GenerateMoves(moves, GEN_ALL, false);

	auto stopTime = std::chrono::high_resolution_clock::now();
	execTime = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime).count();
	std::cout << "MoveGen performed in " << execTime << " microseconds" << std::endl;
}

void Perft::Check(Board board, int depth)
{
	board.Display();
	MoveGenSpeedCheck(board);
	printf("\n");
	// leaf node check
	for (int i = 1; i <= depth; i++)
	{
		auto execTime = 0.0;
		auto startTime = std::chrono::high_resolution_clock::now();
		LeafNodeCheck(board, i);
		auto stopTime = std::chrono::high_resolution_clock::now();
		execTime = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime).count();
		std::cout << "LeafNodeCheck performed in " << (execTime / 1000000.0) << " seconds" << std::endl;
		printf("Depth: %d Leaf Nodes: %ld\n", i, this->leafNodes);
		SetConsoleTextAttribute(hConsoleOut, 0xC);
		printf("Speed: %ld nps (nodes per second)\n", (long)(this->leafNodes / (execTime / 1000000.0)));
		SetConsoleTextAttribute(hConsoleOut, 0x7);
		this->leafNodes = 0;
	}
}
