#pragma once

#include "helper.h"

class Board
{
	private:

		std::vector<int> boardState;

		SIDE side = SIDE_WHITE;
		int enPassantSquare = -1;
		bool whiteKingsideCastle = false;
		bool whiteQueensideCastle = false;
		bool blackKingsideCastle = false;
		bool blackQueensideCastle = false;

	public:

		void Reset();

		void Init(std::string fen);

		void Display();

		void DisplayInfo();

		int Evaluate();

		int EvaluatePSQT();

		int EvaluateAll();

		void SwitchSide();

		SIDE GetSide();

		bool IsSquareAttacked(int square, SIDE byWho);

		bool IsInCheck(SIDE who);

		std::vector<MOVE> ExtractLegalMoves(std::vector<MOVE> moves);

		void GenPawnMoves(std::vector<MOVE>& moves, int rank, int file, SIDE side, MOVEGEN_TYPE type);

		void GenKnightMoves(std::vector<MOVE>& moves, int rank, int file, SIDE side, MOVEGEN_TYPE type);

		void GenBishopMoves(std::vector<MOVE>& moves, int rank, int file, SIDE side, MOVEGEN_TYPE type);

		void GenRookMoves(std::vector<MOVE>& moves, int rank, int file, SIDE side, MOVEGEN_TYPE type);

		void GenQueenMoves(std::vector<MOVE>& moves, int rank, int file, SIDE side, MOVEGEN_TYPE type);

		void GenKingMoves(std::vector<MOVE>& moves, int rank, int file, SIDE side, MOVEGEN_TYPE type);

		void GenerateMoves(std::vector<MOVE>& moves, MOVEGEN_TYPE type, bool sort);

		MOVE StringToMove(std::string moveStr);

		std::string MoveToString(MOVE m);

		void DisplayMoves(std::vector<MOVE> moves);

		void MakeMove(MOVE move);

		void DisplayPv(std::vector<MOVE> pv);

		std::vector<double> ToTensor();

		Board();

		~Board();
};