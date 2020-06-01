#include "board.h"

void Board::Reset()
{
	this->boardState.clear();
	for (int i = 0; i < 120; ++i)
	{
		this->boardState.push_back(NONE_SQUARE);
	}
}

void Board::Init(std::string fen)
{
	Reset();

	std::vector<std::vector<int>> bp;
	std::vector<int> temp;
	int i;

	for (i = 0; i < fen.size(); ++i)
	{
		if (temp.size() == 8)
		{
			bp.push_back(temp);
			temp.clear();
		}

		switch (fen[i])
		{
			case 'p':
				temp.push_back(BLACK_PAWN);
				break;
			case 'n':
				temp.push_back(BLACK_KNIGHT);
				break;
			case 'b':
				temp.push_back(BLACK_BISHOP);
				break;
			case 'r':
				temp.push_back(BLACK_ROOK);
				break;
			case 'q':
				temp.push_back(BLACK_QUEEN);
				break;
			case 'k':
				temp.push_back(BLACK_KING);
				break;
				// white pieces
			case 'P':
				temp.push_back(WHITE_PAWN);
				break;
			case 'N':
				temp.push_back(WHITE_KNIGHT);
				break;
			case 'B':
				temp.push_back(WHITE_BISHOP);
				break;
			case 'R':
				temp.push_back(WHITE_ROOK);
				break;
			case 'Q':
				temp.push_back(WHITE_QUEEN);
				break;
			case 'K':
				temp.push_back(WHITE_KING);
				break;

				//empty
			case '1':
				for (int j = 0; j < 1; j++)
				{
					temp.push_back(EMPTY_SQUARE);
				}
				break;
			case '2':
				for (int j = 0; j < 2; j++)
				{
					temp.push_back(EMPTY_SQUARE);
				}
				break;
			case '3':
				for (int j = 0; j < 3; j++)
				{
					temp.push_back(EMPTY_SQUARE);
				}
				break;
			case '4':
				for (int j = 0; j < 4; j++)
				{
					temp.push_back(EMPTY_SQUARE);
				}
				break;
			case '5':
				for (int j = 0; j < 5; j++)
				{
					temp.push_back(EMPTY_SQUARE);
				}
				break;
			case '6':
				for (int j = 0; j < 6; j++)
				{
					temp.push_back(EMPTY_SQUARE);
				}
				break;
			case '7':
				for (int j = 0; j < 7; j++)
				{
					temp.push_back(EMPTY_SQUARE);
				}
				break;
			case '8':
				for (int j = 0; j < 8; j++)
				{
					temp.push_back(EMPTY_SQUARE);
				}
				break;

			case ' ':
				goto exitFEN;
		}
	}

exitFEN:

	++i;

	if (fen[i] == 'w')
	{
		this->side = SIDE_WHITE;
	}
	else
	{
		this->side = SIDE_BLACK;
	}

	i += 2;

	for (i; i < fen.size(); ++i)
	{
		switch (fen[i])
		{
			case 'K':
				this->whiteKingsideCastle = true;
				break;
			case 'Q':
				this->whiteQueensideCastle = true;
				break;
			case 'k':
				this->blackKingsideCastle = true;
				break;
			case 'q':
				this->blackQueensideCastle = true;
				break;
			case ' ':
				goto exitFEN2;
		}
	}

exitFEN2:

	if (fen[i + 1] != '-')
	{
		int f = LetterToFile(fen[i + 1]);
		int r = fen[i + 2] - '0';
		r = 8 - r;
		this->enPassantSquare = SquareTo120(r, f);
	}
	else
	{
		this->enPassantSquare = 0;
	}

	for (int j = 0; j < 8; ++j)
	{
		for (int k = 0; k < 8; ++k)
		{
			this->boardState[SquareTo120(j, k)] = bp[j][k];
		}
	}
}

void Board::Display()
{
	printf("    -----------------\n");
	for (int i = 0; i < 8; ++i)
	{
		printf(" %d |", 8 - i);
		for (int j = 0; j < 8; ++j)
		{
			int sq = SquareTo120(i, j);

			switch (this->boardState[sq])
			{
				case EMPTY_SQUARE:
					printf(" .");
					break;

				case WHITE_PAWN:
					SetConsoleTextAttribute(hConsoleOut, 0xC);
					printf(" P");
					SetConsoleTextAttribute(hConsoleOut, 0x7);
					break;
				case WHITE_KNIGHT:
					SetConsoleTextAttribute(hConsoleOut, 0xC);
					printf(" N");
					SetConsoleTextAttribute(hConsoleOut, 0x7);
					break;
				case WHITE_BISHOP:
					SetConsoleTextAttribute(hConsoleOut, 0xC);
					printf(" B");
					SetConsoleTextAttribute(hConsoleOut, 0x7);
					break;
				case WHITE_ROOK:
					SetConsoleTextAttribute(hConsoleOut, 0xC);
					printf(" R");
					SetConsoleTextAttribute(hConsoleOut, 0x7);
					break;
				case WHITE_QUEEN:
					SetConsoleTextAttribute(hConsoleOut, 0xC);
					printf(" Q");
					SetConsoleTextAttribute(hConsoleOut, 0x7);
					break;
				case WHITE_KING:
					SetConsoleTextAttribute(hConsoleOut, 0xC);
					printf(" K");
					SetConsoleTextAttribute(hConsoleOut, 0x7);
					break;

				case BLACK_PAWN:
					SetConsoleTextAttribute(hConsoleOut, 6);
					printf(" p");
					SetConsoleTextAttribute(hConsoleOut, 0x7);
					break;
				case BLACK_KNIGHT:
					SetConsoleTextAttribute(hConsoleOut, 6);
					printf(" n");
					SetConsoleTextAttribute(hConsoleOut, 0x7);
					break;
				case BLACK_BISHOP:
					SetConsoleTextAttribute(hConsoleOut, 6);
					printf(" b");
					SetConsoleTextAttribute(hConsoleOut, 0x7);
					break;
				case BLACK_ROOK:
					SetConsoleTextAttribute(hConsoleOut, 6);
					printf(" r");
					SetConsoleTextAttribute(hConsoleOut, 0x7);
					break;
				case BLACK_QUEEN:
					SetConsoleTextAttribute(hConsoleOut, 6);
					printf(" q");
					SetConsoleTextAttribute(hConsoleOut, 0x7);
					break;
				case BLACK_KING:
					SetConsoleTextAttribute(hConsoleOut, 6);
					printf(" k");
					SetConsoleTextAttribute(hConsoleOut, 0x7);
					break;
				default:
					printf(" ?");
					break;
			}
		}
		printf(" |\n");
	}
	printf("    -----------------\n");
	printf("     a b c d e f g h \n");
}

void Board::DisplayInfo()
{
	if (this->side == SIDE_WHITE)
	{
		printf("WHITE TO MOVE\n");
	}
	else
	{
		printf("BLACK TO MOVE\n");
	}
	printf("CASTLING RIGHTS:\n");
	printf("\tWhite Kingside: %s\n", this->whiteKingsideCastle ? "true" : "false");
	printf("\tWhite Queenside: %s\n", this->whiteQueensideCastle ? "true" : "false");
	printf("\tBlack Kingside: %s\n", this->blackKingsideCastle ? "true" : "false");
	printf("\tBlack Queenside: %s\n", this->blackQueensideCastle ? "true" : "false");
	printf("ENPASSANT SQUARE: %d\n", this->enPassantSquare);
}

double Board::Evaluate()
{
	double score = 0.0;
	std::vector<MOVE> temp;

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			int sq = SquareTo120(i, j);
			int pc = this->boardState[sq];
			score += (double)(pc * 1000);
			switch (pc)
			{
				case WHITE_KNIGHT:
					GenKnightMoves(temp, i, j, SIDE_WHITE, GEN_QUIET);
					score += (double)temp.size();
					temp.clear();
					break;
				case WHITE_BISHOP:
					GenBishopMoves(temp, i, j, SIDE_WHITE, GEN_QUIET);
					score += (double)temp.size();
					temp.clear();
					break;
				case WHITE_ROOK:
					GenRookMoves(temp, i, j, SIDE_WHITE, GEN_QUIET);
					score += (double)temp.size();
					temp.clear();
					break;

				case BLACK_KNIGHT:
					GenKnightMoves(temp, i, j, SIDE_BLACK, GEN_QUIET);
					score -= (double)temp.size();
					temp.clear();
					break;
				case BLACK_BISHOP:
					GenBishopMoves(temp, i, j, SIDE_BLACK, GEN_QUIET);
					score -= (double)temp.size();
					temp.clear();
					break;
				case BLACK_ROOK:
					GenRookMoves(temp, i, j, SIDE_BLACK, GEN_QUIET);
					score -= (double)temp.size();
					temp.clear();
					break;
			}
		}
	}
	if (this->side == SIDE_WHITE)
	{
		return score;
	}
	else
	{
		return -score;
	}
}

int Board::EvaluateMCTS()
{
	int score = 0;
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			score += this->boardState[SquareTo120(i, j)];
		}
	}
	return score;
}

void Board::SwitchSide()
{
	if (this->side == SIDE_WHITE)
	{
		this->side = SIDE_BLACK;
	}
	else
	{
		this->side = SIDE_WHITE;
	}
}

SIDE Board::GetSide()
{
	return this->side;
}

bool Board::IsSquareAttacked(int square, SIDE byWho)
{
	if (byWho == SIDE_WHITE)
	{
		if (this->boardState[square + 9] == WHITE_PAWN ||
			this->boardState[square + 11] == WHITE_PAWN)
		{
			return true;
		}

		for (int i = 0; i < 8; ++i)
		{
			if (this->boardState[square + KnightDir[i]] == WHITE_KNIGHT)
			{
				return true;
			}
		}

		for (int i = 0; i < 4; ++i)
		{
			int d = RookDir[i];
			int newSquare = square + d;

			int piece = this->boardState[newSquare];
			while (piece != NONE_SQUARE)
			{
				if (piece != EMPTY_SQUARE)
				{
					if (piece == WHITE_ROOK || piece == WHITE_QUEEN)
					{
						return true;
					}
					break;
				}
				newSquare += d;
				piece = this->boardState[newSquare];
			}
		}

		for (int i = 0; i < 4; ++i)
		{
			int d = BishopDir[i];
			int newSquare = square + d;

			int piece = this->boardState[newSquare];
			while (piece != NONE_SQUARE)
			{
				if (piece != EMPTY_SQUARE)
				{
					if (piece == WHITE_BISHOP || piece == WHITE_QUEEN)
					{
						return true;
					}
					break;
				}
				newSquare += d;
				piece = this->boardState[newSquare];
			}
		}

		for (int i = 0; i < 8; ++i)
		{
			if (this->boardState[square + KingDir[i]] == WHITE_KING)
			{
				return true;
			}
		}

	}
	else // black
	{
		if (this->boardState[square - 9] == BLACK_PAWN ||
			this->boardState[square - 11] == BLACK_PAWN)
		{
			return true;
		}

		for (int i = 0; i < 8; ++i)
		{
			if (this->boardState[square + KnightDir[i]] == BLACK_KNIGHT)
			{
				return true;
			}
		}

		for (int i = 0; i < 4; ++i)
		{
			int d = RookDir[i];
			int newSquare = square + d;

			int piece = this->boardState[newSquare];
			while (piece != NONE_SQUARE)
			{
				if (piece != EMPTY_SQUARE)
				{
					if (piece == BLACK_ROOK || piece == BLACK_QUEEN)
					{
						return true;
					}
					break;
				}
				newSquare += d;
				piece = this->boardState[newSquare];
			}
		}

		for (int i = 0; i < 4; ++i)
		{
			int d = BishopDir[i];
			int newSquare = square + d;

			int piece = this->boardState[newSquare];
			while (piece != NONE_SQUARE)
			{
				if (piece != EMPTY_SQUARE)
				{
					if (piece == BLACK_BISHOP || piece == BLACK_QUEEN)
					{
						return true;
					}
					break;
				}
				newSquare += d;
				piece = this->boardState[newSquare];
			}
		}

		for (int i = 0; i < 8; ++i)
		{
			if (this->boardState[square + KingDir[i]] == BLACK_KING)
			{
				return true;
			}
		}
	}

	return false;
}

bool Board::IsInCheck(SIDE who)
{
	for (int i = 0; i < this->boardState.size(); ++i)
	{
		if (who == SIDE_WHITE)
		{
			if (this->boardState[i] == WHITE_KING)
			{
				return IsSquareAttacked(i, SIDE_BLACK);
			}
		}
		else
		{
			if (this->boardState[i] == BLACK_KING)
			{
				return IsSquareAttacked(i, SIDE_WHITE);
			}
		}
	}
	return false;
}

std::vector<MOVE> Board::ExtractLegalMoves(std::vector<MOVE> moves)
{
	std::vector<MOVE> legalMoves;
	for (int i = 0; i < moves.size(); i++)
	{
		std::vector<int> tb = this->boardState;
		int tenPas = this->enPassantSquare;
		SIDE tside = this->side;
		bool twhiteKingsideCastle = this->whiteKingsideCastle;
		bool twhiteQueensideCastle = this->whiteQueensideCastle;
		bool tblackKingsideCastle = this->blackKingsideCastle;
		bool tblackQueensideCastle = this->blackQueensideCastle;

		MakeMove(moves[i]);
		if (!IsInCheck(tside))
		{
			legalMoves.push_back(moves[i]);
		}

		this->boardState = tb;
		this->enPassantSquare = tenPas;
		this->side = tside;
		this->whiteKingsideCastle = twhiteKingsideCastle;
		this->whiteQueensideCastle = twhiteQueensideCastle;
		this->blackKingsideCastle = tblackKingsideCastle;
		this->blackQueensideCastle = tblackQueensideCastle;
	}
	return legalMoves;
}

void Board::GenPawnMoves(std::vector<MOVE>& moves, int rank, int file, SIDE side, MOVEGEN_TYPE type)
{
	std::vector<MOVE> violent;
	std::vector<MOVE> quiet;

	MOVE m;
	int square = SquareTo120(rank, file);
	int enPas = this->enPassantSquare;

	m.from = square;

	if (side == SIDE_WHITE)
	{
		if (rank == 1) // promotion
		{
			if (this->boardState[square - 10] == EMPTY_SQUARE)
			{
				m.type = MOVE_VIOLENT_TYPE;
				m.to = square - 10;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.score = PxQ;
				m.promoteTo = WHITE_QUEEN;
				quiet.push_back(m);
				m.type = MOVE_QUIET_TYPE;
				m.score = KxP;
				m.promoteTo = WHITE_ROOK;
				quiet.push_back(m);
				m.promoteTo = WHITE_BISHOP;
				quiet.push_back(m);
				m.promoteTo = WHITE_KNIGHT;
				quiet.push_back(m);
			}

			if (this->boardState[square - 9] != NONE_SQUARE &&
				this->boardState[square - 9] < 0)
			{
				switch (abs(this->boardState[square - 9]))
				{
					case WHITE_PAWN:
						m.score = PxP;
						break;
					case WHITE_KNIGHT:
						m.score = PxN;
						break;
					case WHITE_BISHOP:
						m.score = PxB;
						break;
					case WHITE_ROOK:
						m.score = PxR;
						break;
					case WHITE_QUEEN:
						m.score = PxQ;
						break;
				}
				m.type = MOVE_VIOLENT_TYPE;
				m.to = square - 9;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = WHITE_QUEEN;
				violent.push_back(m);
				m.promoteTo = WHITE_ROOK;
				violent.push_back(m);
				m.promoteTo = WHITE_BISHOP;
				violent.push_back(m);
				m.promoteTo = WHITE_KNIGHT;
				violent.push_back(m);
			}

			if (this->boardState[square - 11] != NONE_SQUARE &&
				this->boardState[square - 11] < 0)
			{
				switch (abs(this->boardState[square - 11]))
				{
					case WHITE_PAWN:
						m.score = PxP;
						break;
					case WHITE_KNIGHT:
						m.score = PxN;
						break;
					case WHITE_BISHOP:
						m.score = PxB;
						break;
					case WHITE_ROOK:
						m.score = PxR;
						break;
					case WHITE_QUEEN:
						m.score = PxQ;
						break;
				}
				m.type = MOVE_VIOLENT_TYPE;
				m.to = square - 11;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = WHITE_QUEEN;
				violent.push_back(m);
				m.promoteTo = WHITE_ROOK;
				violent.push_back(m);
				m.promoteTo = WHITE_BISHOP;
				violent.push_back(m);
				m.promoteTo = WHITE_KNIGHT;
				violent.push_back(m);
			}
		}
		else
		{
			if (this->boardState[square - 10] == EMPTY_SQUARE)
			{
				m.score = 0;
				m.type = MOVE_QUIET_TYPE;
				m.to = square - 10;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = WHITE_PAWN;
				quiet.push_back(m);

				if (rank == 6 && this->boardState[square - 20] == EMPTY_SQUARE)
				{
					m.score = 0;
					m.type = MOVE_QUIET_TYPE;
					m.to = square - 20;
					m.castling = NO_CASTLING_MOVE;
					m.enPas = false;
					m.promoteTo = WHITE_PAWN;
					quiet.push_back(m);
				}
			}

			if (this->boardState[square - 9] != NONE_SQUARE &&
				this->boardState[square - 9] < 0)
			{
				switch (abs(this->boardState[square - 9]))
				{
					case WHITE_PAWN:
						m.score = PxP;
						break;
					case WHITE_KNIGHT:
						m.score = PxN;
						break;
					case WHITE_BISHOP:
						m.score = PxB;
						break;
					case WHITE_ROOK:
						m.score = PxR;
						break;
					case WHITE_QUEEN:
						m.score = PxQ;
						break;
				}
				m.type = MOVE_VIOLENT_TYPE;
				m.to = square - 9;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = WHITE_PAWN;
				violent.push_back(m);
			}

			if (this->boardState[square - 11] != NONE_SQUARE &&
				this->boardState[square - 11] < 0)
			{
				switch (abs(this->boardState[square - 11]))
				{
					case WHITE_PAWN:
						m.score = PxP;
						break;
					case WHITE_KNIGHT:
						m.score = PxN;
						break;
					case WHITE_BISHOP:
						m.score = PxB;
						break;
					case WHITE_ROOK:
						m.score = PxR;
						break;
					case WHITE_QUEEN:
						m.score = PxQ;
						break;
				}
				m.type = MOVE_VIOLENT_TYPE;
				m.to = square - 11;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = WHITE_PAWN;
				violent.push_back(m);
			}

			// enpas
			if (this->boardState[square - 9] != NONE_SQUARE &&
				square - 9 == enPas)
			{
				m.score = PxP;
				m.type = MOVE_VIOLENT_TYPE;
				m.to = square - 9;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = true;
				m.promoteTo = WHITE_PAWN;
				violent.push_back(m);
			}

			if (this->boardState[square - 11] != NONE_SQUARE &&
				square - 11 == enPas)
			{
				m.score = PxP;
				m.type = MOVE_VIOLENT_TYPE;
				m.to = square - 11;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = true;
				m.promoteTo = WHITE_PAWN;
				violent.push_back(m);
			}
		}
	}
	else
	{
		if (rank == 6) // promotion
		{
			if (this->boardState[square + 10] == EMPTY_SQUARE)
			{
				m.type = MOVE_VIOLENT_TYPE;
				m.to = square + 10;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.score = PxQ;
				m.promoteTo = BLACK_QUEEN;
				quiet.push_back(m);
				m.type = MOVE_QUIET_TYPE;
				m.score = KxP;
				m.promoteTo = BLACK_ROOK;
				quiet.push_back(m);
				m.promoteTo = BLACK_BISHOP;
				quiet.push_back(m);
				m.promoteTo = BLACK_KNIGHT;
				quiet.push_back(m);
			}

			if (this->boardState[square + 9] != NONE_SQUARE &&
				this->boardState[square + 9] > 0)
			{
				switch (abs(this->boardState[square + 9]))
				{
					case WHITE_PAWN:
						m.score = PxP;
						break;
					case WHITE_KNIGHT:
						m.score = PxN;
						break;
					case WHITE_BISHOP:
						m.score = PxB;
						break;
					case WHITE_ROOK:
						m.score = PxR;
						break;
					case WHITE_QUEEN:
						m.score = PxQ;
						break;
				}
				m.type = MOVE_VIOLENT_TYPE;
				m.to = square + 9;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = BLACK_QUEEN;
				violent.push_back(m);
				m.promoteTo = BLACK_ROOK;
				violent.push_back(m);
				m.promoteTo = BLACK_BISHOP;
				violent.push_back(m);
				m.promoteTo = BLACK_KNIGHT;
				violent.push_back(m);
			}

			if (this->boardState[square + 11] != NONE_SQUARE &&
				this->boardState[square + 11] > 0)
			{
				switch (abs(this->boardState[square + 11]))
				{
					case WHITE_PAWN:
						m.score = PxP;
						break;
					case WHITE_KNIGHT:
						m.score = PxN;
						break;
					case WHITE_BISHOP:
						m.score = PxB;
						break;
					case WHITE_ROOK:
						m.score = PxR;
						break;
					case WHITE_QUEEN:
						m.score = PxQ;
						break;
				}
				m.type = MOVE_VIOLENT_TYPE;
				m.to = square + 11;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = BLACK_QUEEN;
				violent.push_back(m);
				m.promoteTo = BLACK_ROOK;
				violent.push_back(m);
				m.promoteTo = BLACK_BISHOP;
				violent.push_back(m);
				m.promoteTo = BLACK_KNIGHT;
				violent.push_back(m);
			}
		}
		else
		{
			if (this->boardState[square + 10] == EMPTY_SQUARE)
			{
				m.score = 0;
				m.type = MOVE_QUIET_TYPE;
				m.to = square + 10;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = BLACK_PAWN;
				quiet.push_back(m);

				if (rank == 1 && this->boardState[square + 20] == EMPTY_SQUARE)
				{
					m.score = 0;
					m.type = MOVE_QUIET_TYPE;
					m.to = square + 20;
					m.castling = NO_CASTLING_MOVE;
					m.enPas = false;
					m.promoteTo = BLACK_PAWN;
					quiet.push_back(m);
				}
			}

			if (this->boardState[square + 9] != NONE_SQUARE &&
				this->boardState[square + 9] > 0)
			{
				switch (abs(this->boardState[square + 9]))
				{
					case WHITE_PAWN:
						m.score = PxP;
						break;
					case WHITE_KNIGHT:
						m.score = PxN;
						break;
					case WHITE_BISHOP:
						m.score = PxB;
						break;
					case WHITE_ROOK:
						m.score = PxR;
						break;
					case WHITE_QUEEN:
						m.score = PxQ;
						break;
				}
				m.type = MOVE_VIOLENT_TYPE;
				m.to = square + 9;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = BLACK_PAWN;
				violent.push_back(m);
			}

			if (this->boardState[square + 11] != NONE_SQUARE &&
				this->boardState[square + 11] > 0)
			{
				switch (abs(this->boardState[square + 11]))
				{
					case WHITE_PAWN:
						m.score = PxP;
						break;
					case WHITE_KNIGHT:
						m.score = PxN;
						break;
					case WHITE_BISHOP:
						m.score = PxB;
						break;
					case WHITE_ROOK:
						m.score = PxR;
						break;
					case WHITE_QUEEN:
						m.score = PxQ;
						break;
				}
				m.type = MOVE_VIOLENT_TYPE;
				m.to = square + 11;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = BLACK_PAWN;
				violent.push_back(m);
			}

			// enpas
			if (this->boardState[square + 9] != NONE_SQUARE &&
				square + 9 == enPas)
			{
				m.score = PxP;
				m.type = MOVE_VIOLENT_TYPE;
				m.to = square + 9;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = true;
				m.promoteTo = BLACK_PAWN;
				violent.push_back(m);
			}

			if (this->boardState[square + 11] != NONE_SQUARE &&
				square + 11 == enPas)
			{
				m.score = PxP;
				m.type = MOVE_VIOLENT_TYPE;
				m.to = square + 11;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = true;
				m.promoteTo = BLACK_PAWN;
				violent.push_back(m);
			}
		}
	}

	if (type == GEN_VIOLENT)
	{
		moves = violent;
	}
	else if (type == GEN_QUIET)
	{
		moves = quiet;
	}
	else // all
	{
		moves = violent;
		moves.insert(moves.end(), quiet.begin(), quiet.end());
	}
}

void Board::GenKnightMoves(std::vector<MOVE>& moves, int rank, int file, SIDE side, MOVEGEN_TYPE type)
{
	std::vector<MOVE> violent;
	std::vector<MOVE> quiet;

	MOVE m;
	int square = SquareTo120(rank, file);

	m.from = square;

	if (side == SIDE_WHITE)
	{
		for (int i = 0; i < 8; ++i)
		{
			if (this->boardState[square + KnightDir[i]] != NONE_SQUARE &&
				this->boardState[square + KnightDir[i]] <= 0)
			{
				m.to = square + KnightDir[i];
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = WHITE_KNIGHT;

				if (this->boardState[square + KnightDir[i]] == EMPTY_SQUARE)
				{
					m.score = 0;
					m.type = MOVE_QUIET_TYPE;
					quiet.push_back(m);
				}
				else
				{
					switch (abs(this->boardState[square + KnightDir[i]]))
					{
						case WHITE_PAWN:
							m.score = NxP;
							break;
						case WHITE_KNIGHT:
							m.score = NxN;
							break;
						case WHITE_BISHOP:
							m.score = NxB;
							break;
						case WHITE_ROOK:
							m.score = NxR;
							break;
						case WHITE_QUEEN:
							m.score = NxQ;
							break;
					}
					m.type = MOVE_VIOLENT_TYPE;
					violent.push_back(m);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 8; ++i)
		{
			if (this->boardState[square + KnightDir[i]] != NONE_SQUARE &&
				this->boardState[square + KnightDir[i]] >= 0)
			{
				m.to = square + KnightDir[i];
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = BLACK_KNIGHT;

				if (this->boardState[square + KnightDir[i]] == EMPTY_SQUARE)
				{
					m.score = 0;
					m.type = MOVE_QUIET_TYPE;
					quiet.push_back(m);
				}
				else
				{
					switch (abs(this->boardState[square + KnightDir[i]]))
					{
						case WHITE_PAWN:
							m.score = NxP;
							break;
						case WHITE_KNIGHT:
							m.score = NxN;
							break;
						case WHITE_BISHOP:
							m.score = NxB;
							break;
						case WHITE_ROOK:
							m.score = NxR;
							break;
						case WHITE_QUEEN:
							m.score = NxQ;
							break;
					}
					m.type = MOVE_VIOLENT_TYPE;
					violent.push_back(m);
				}
			}
		}
	}

	if (type == GEN_VIOLENT)
	{
		moves = violent;
	}
	else if (type == GEN_QUIET)
	{
		moves = quiet;
	}
	else // all
	{
		moves = violent;
		moves.insert(moves.end(), quiet.begin(), quiet.end());
	}
}

void Board::GenBishopMoves(std::vector<MOVE>& moves, int rank, int file, SIDE side, MOVEGEN_TYPE type)
{
	std::vector<MOVE> violent;
	std::vector<MOVE> quiet;

	MOVE m;
	int square = SquareTo120(rank, file);

	m.from = square;

	if (side == SIDE_WHITE)
	{
		for (int i = 0; i < 4; ++i)
		{
			int d = BishopDir[i];
			int newSquare = square + d;

			int piece = this->boardState[newSquare];
			while (piece != NONE_SQUARE)
			{
				if (piece > 0)
				{
					break;
				}
				if (piece < 0)
				{
					switch (abs(piece))
					{
						case WHITE_PAWN:
							m.score = BxP;
							break;
						case WHITE_KNIGHT:
							m.score = BxN;
							break;
						case WHITE_BISHOP:
							m.score = BxB;
							break;
						case WHITE_ROOK:
							m.score = BxR;
							break;
						case WHITE_QUEEN:
							m.score = BxQ;
							break;
					}
					m.type = MOVE_VIOLENT_TYPE;
					m.to = newSquare;
					m.castling = NO_CASTLING_MOVE;
					m.enPas = false;
					m.promoteTo = WHITE_BISHOP;
					violent.push_back(m);
					break;
				}
				m.score = 0;
				m.type = MOVE_QUIET_TYPE;
				m.to = newSquare;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = WHITE_BISHOP;
				quiet.push_back(m);

				newSquare += d;
				piece = this->boardState[newSquare];
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			int d = BishopDir[i];
			int newSquare = square + d;

			int piece = this->boardState[newSquare];
			while (piece != NONE_SQUARE)
			{
				if (piece < 0)
				{
					break;
				}
				if (piece > 0)
				{
					switch (abs(piece))
					{
						case WHITE_PAWN:
							m.score = BxP;
							break;
						case WHITE_KNIGHT:
							m.score = BxN;
							break;
						case WHITE_BISHOP:
							m.score = BxB;
							break;
						case WHITE_ROOK:
							m.score = BxR;
							break;
						case WHITE_QUEEN:
							m.score = BxQ;
							break;
					}
					m.type = MOVE_VIOLENT_TYPE;
					m.to = newSquare;
					m.castling = NO_CASTLING_MOVE;
					m.enPas = false;
					m.promoteTo = BLACK_BISHOP;
					violent.push_back(m);
					break;
				}
				m.score = 0;
				m.type = MOVE_QUIET_TYPE;
				m.to = newSquare;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = BLACK_BISHOP;
				quiet.push_back(m);

				newSquare += d;
				piece = this->boardState[newSquare];
			}
		}
	}

	if (type == GEN_VIOLENT)
	{
		moves = violent;
	}
	else if (type == GEN_QUIET)
	{
		moves = quiet;
	}
	else // all
	{
		moves = violent;
		moves.insert(moves.end(), quiet.begin(), quiet.end());
	}
}

void Board::GenRookMoves(std::vector<MOVE>& moves, int rank, int file, SIDE side, MOVEGEN_TYPE type)
{
	std::vector<MOVE> violent;
	std::vector<MOVE> quiet;

	MOVE m;
	int square = SquareTo120(rank, file);

	m.from = square;

	if (side == SIDE_WHITE)
	{
		for (int i = 0; i < 4; ++i)
		{
			int d = RookDir[i];
			int newSquare = square + d;

			int piece = this->boardState[newSquare];
			while (piece != NONE_SQUARE)
			{
				if (piece > 0)
				{
					break;
				}
				if (piece < 0)
				{
					switch (abs(piece))
					{
						case WHITE_PAWN:
							m.score = RxP;
							break;
						case WHITE_KNIGHT:
							m.score = RxN;
							break;
						case WHITE_BISHOP:
							m.score = RxB;
							break;
						case WHITE_ROOK:
							m.score = RxR;
							break;
						case WHITE_QUEEN:
							m.score = RxQ;
							break;
					}
					m.type = MOVE_VIOLENT_TYPE;
					m.to = newSquare;
					m.castling = NO_CASTLING_MOVE;
					m.enPas = false;
					m.promoteTo = WHITE_ROOK;
					violent.push_back(m);
					break;
				}
				m.score = 0;
				m.type = MOVE_QUIET_TYPE;
				m.to = newSquare;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = WHITE_ROOK;
				quiet.push_back(m);

				newSquare += d;
				piece = this->boardState[newSquare];
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			int d = RookDir[i];
			int newSquare = square + d;

			int piece = this->boardState[newSquare];
			while (piece != NONE_SQUARE)
			{
				if (piece < 0)
				{
					break;
				}
				if (piece > 0)
				{
					switch (abs(piece))
					{
						case WHITE_PAWN:
							m.score = RxP;
							break;
						case WHITE_KNIGHT:
							m.score = RxN;
							break;
						case WHITE_BISHOP:
							m.score = RxB;
							break;
						case WHITE_ROOK:
							m.score = RxR;
							break;
						case WHITE_QUEEN:
							m.score = RxQ;
							break;
					}
					m.type = MOVE_VIOLENT_TYPE;
					m.to = newSquare;
					m.castling = NO_CASTLING_MOVE;
					m.enPas = false;
					m.promoteTo = BLACK_ROOK;
					violent.push_back(m);
					break;
				}
				m.score = 0;
				m.type = MOVE_QUIET_TYPE;
				m.to = newSquare;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = BLACK_ROOK;
				quiet.push_back(m);

				newSquare += d;
				piece = this->boardState[newSquare];
			}
		}
	}

	if (type == GEN_VIOLENT)
	{
		moves = violent;
	}
	else if (type == GEN_QUIET)
	{
		moves = quiet;
	}
	else // all
	{
		moves = violent;
		moves.insert(moves.end(), quiet.begin(), quiet.end());
	}
}

void Board::GenQueenMoves(std::vector<MOVE>& moves, int rank, int file, SIDE side, MOVEGEN_TYPE type)
{
	std::vector<MOVE> violent;
	std::vector<MOVE> quiet;

	MOVE m;
	int square = SquareTo120(rank, file);

	m.from = square;

	if (side == SIDE_WHITE)
	{
		for (int i = 0; i < 4; ++i)
		{
			int d = BishopDir[i];
			int newSquare = square + d;

			int piece = this->boardState[newSquare];
			while (piece != NONE_SQUARE)
			{
				if (piece > 0)
				{
					break;
				}
				if (piece < 0)
				{
					switch (abs(piece))
					{
						case WHITE_PAWN:
							m.score = QxP;
							break;
						case WHITE_KNIGHT:
							m.score = QxN;
							break;
						case WHITE_BISHOP:
							m.score = QxB;
							break;
						case WHITE_ROOK:
							m.score = QxR;
							break;
						case WHITE_QUEEN:
							m.score = QxQ;
							break;
					}
					m.type = MOVE_VIOLENT_TYPE;
					m.to = newSquare;
					m.castling = NO_CASTLING_MOVE;
					m.enPas = false;
					m.promoteTo = WHITE_QUEEN;
					violent.push_back(m);
					break;
				}
				m.score = 0;
				m.type = MOVE_QUIET_TYPE;
				m.to = newSquare;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = WHITE_QUEEN;
				quiet.push_back(m);

				newSquare += d;
				piece = this->boardState[newSquare];
			}
		}

		for (int i = 0; i < 4; ++i)
		{
			int d = RookDir[i];
			int newSquare = square + d;

			int piece = this->boardState[newSquare];
			while (piece != NONE_SQUARE)
			{
				if (piece > 0)
				{
					break;
				}
				if (piece < 0)
				{
					switch (abs(piece))
					{
						case WHITE_PAWN:
							m.score = QxP;
							break;
						case WHITE_KNIGHT:
							m.score = QxN;
							break;
						case WHITE_BISHOP:
							m.score = QxB;
							break;
						case WHITE_ROOK:
							m.score = QxR;
							break;
						case WHITE_QUEEN:
							m.score = QxQ;
							break;
					}
					m.type = MOVE_VIOLENT_TYPE;
					m.to = newSquare;
					m.castling = NO_CASTLING_MOVE;
					m.enPas = false;
					m.promoteTo = WHITE_QUEEN;
					violent.push_back(m);
					break;
				}
				m.score = 0;
				m.type = MOVE_QUIET_TYPE;
				m.to = newSquare;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = WHITE_QUEEN;
				quiet.push_back(m);

				newSquare += d;
				piece = this->boardState[newSquare];
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			int d = BishopDir[i];
			int newSquare = square + d;

			int piece = this->boardState[newSquare];
			while (piece != NONE_SQUARE)
			{
				if (piece < 0)
				{
					break;
				}
				if (piece > 0)
				{
					switch (abs(piece))
					{
						case WHITE_PAWN:
							m.score = QxP;
							break;
						case WHITE_KNIGHT:
							m.score = QxN;
							break;
						case WHITE_BISHOP:
							m.score = QxB;
							break;
						case WHITE_ROOK:
							m.score = QxR;
							break;
						case WHITE_QUEEN:
							m.score = QxQ;
							break;
					}
					m.type = MOVE_VIOLENT_TYPE;
					m.to = newSquare;
					m.castling = NO_CASTLING_MOVE;
					m.enPas = false;
					m.promoteTo = BLACK_QUEEN;
					violent.push_back(m);
					break;
				}
				m.score = 0;
				m.type = MOVE_QUIET_TYPE;
				m.to = newSquare;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = BLACK_QUEEN;
				quiet.push_back(m);

				newSquare += d;
				piece = this->boardState[newSquare];
			}
		}

		for (int i = 0; i < 4; ++i)
		{
			int d = RookDir[i];
			int newSquare = square + d;

			int piece = this->boardState[newSquare];
			while (piece != NONE_SQUARE)
			{
				if (piece < 0)
				{
					break;
				}
				if (piece > 0)
				{
					switch (abs(piece))
					{
						case WHITE_PAWN:
							m.score = QxP;
							break;
						case WHITE_KNIGHT:
							m.score = QxN;
							break;
						case WHITE_BISHOP:
							m.score = QxB;
							break;
						case WHITE_ROOK:
							m.score = QxR;
							break;
						case WHITE_QUEEN:
							m.score = QxQ;
							break;
					}
					m.type = MOVE_VIOLENT_TYPE;
					m.to = newSquare;
					m.castling = NO_CASTLING_MOVE;
					m.enPas = false;
					m.promoteTo = BLACK_QUEEN;
					violent.push_back(m);
					break;
				}
				m.score = 0;
				m.type = MOVE_QUIET_TYPE;
				m.to = newSquare;
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = BLACK_QUEEN;
				quiet.push_back(m);

				newSquare += d;
				piece = this->boardState[newSquare];
			}
		}
	}

	if (type == GEN_VIOLENT)
	{
		moves = violent;
	}
	else if (type == GEN_QUIET)
	{
		moves = quiet;
	}
	else // all
	{
		moves = violent;
		moves.insert(moves.end(), quiet.begin(), quiet.end());
	}
}

void Board::GenKingMoves(std::vector<MOVE>& moves, int rank, int file, SIDE side, MOVEGEN_TYPE type)
{
	std::vector<MOVE> violent;
	std::vector<MOVE> quiet;

	MOVE m;
	int square = SquareTo120(rank, file);

	m.from = square;

	if (side == SIDE_WHITE)
	{
		for (int i = 0; i < 8; ++i)
		{
			if (this->boardState[square + KingDir[i]] != NONE_SQUARE &&
				this->boardState[square + KingDir[i]] <= 0 &&
				!IsSquareAttacked(square + KingDir[i], SIDE_BLACK))
			{
				m.to = square + KingDir[i];
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = WHITE_KING;

				if (this->boardState[square + KingDir[i]] == EMPTY_SQUARE)
				{
					m.score = 0;
					m.type = MOVE_QUIET_TYPE;
					quiet.push_back(m);
				}
				else
				{
					switch (abs(this->boardState[square + KingDir[i]]))
					{
						case WHITE_PAWN:
							m.score = KxP;
							break;
						case WHITE_KNIGHT:
							m.score = KxN;
							break;
						case WHITE_BISHOP:
							m.score = KxB;
							break;
						case WHITE_ROOK:
							m.score = KxR;
							break;
						case WHITE_QUEEN:
							m.score = KxQ;
							break;
					}
					m.type = MOVE_VIOLENT_TYPE;
					violent.push_back(m);
				}
			}
		}

		if (this->whiteKingsideCastle && this->boardState[96] == EMPTY_SQUARE &&
			this->boardState[97] == EMPTY_SQUARE && this->boardState[98] == WHITE_ROOK &&
			!IsSquareAttacked(95, SIDE_BLACK) &&
			!IsSquareAttacked(96, SIDE_BLACK) && !IsSquareAttacked(97, SIDE_BLACK))
		{
			m.score = 0;
			m.type = MOVE_QUIET_TYPE;
			m.to = 0;
			m.castling = WHITE_KINGSIDE_CASTLE_MOVE;
			m.enPas = false;
			m.promoteTo = WHITE_KING;
			quiet.push_back(m);
		}

		if (this->whiteQueensideCastle && this->boardState[92] == EMPTY_SQUARE &&
			this->boardState[93] == EMPTY_SQUARE && this->boardState[94] == EMPTY_SQUARE &&
			this->boardState[91] == WHITE_ROOK &&
			!IsSquareAttacked(93, SIDE_BLACK) && !IsSquareAttacked(94, SIDE_BLACK) && !IsSquareAttacked(95, SIDE_BLACK))
		{
			m.score = 0;
			m.type = MOVE_QUIET_TYPE;
			m.to = 0;
			m.castling = WHITE_QUEENSIDE_CASTLE_MOVE;
			m.enPas = false;
			m.promoteTo = WHITE_KING;
			quiet.push_back(m);
		}

	}
	else
	{
		for (int i = 0; i < 8; ++i)
		{
			if (this->boardState[square + KingDir[i]] != NONE_SQUARE &&
				this->boardState[square + KingDir[i]] >= 0 &&
				!IsSquareAttacked(square + KingDir[i], SIDE_WHITE))
			{
				m.to = square + KingDir[i];
				m.castling = NO_CASTLING_MOVE;
				m.enPas = false;
				m.promoteTo = BLACK_KING;

				if (this->boardState[square + KingDir[i]] == EMPTY_SQUARE)
				{
					m.score = 0;
					m.type = MOVE_QUIET_TYPE;
					quiet.push_back(m);
				}
				else
				{
					switch (abs(this->boardState[square + KingDir[i]]))
					{
						case WHITE_PAWN:
							m.score = KxP;
							break;
						case WHITE_KNIGHT:
							m.score = KxN;
							break;
						case WHITE_BISHOP:
							m.score = KxB;
							break;
						case WHITE_ROOK:
							m.score = KxR;
							break;
						case WHITE_QUEEN:
							m.score = KxQ;
							break;
					}
					m.type = MOVE_VIOLENT_TYPE;
					violent.push_back(m);
				}
			}
		}

		if (this->blackKingsideCastle && this->boardState[26] == EMPTY_SQUARE &&
			this->boardState[27] == EMPTY_SQUARE && this->boardState[28] == BLACK_ROOK &&
			!IsSquareAttacked(25, SIDE_WHITE) &&
			!IsSquareAttacked(26, SIDE_WHITE) && !IsSquareAttacked(27, SIDE_WHITE))
		{
			m.score = 0;
			m.type = MOVE_QUIET_TYPE;
			m.to = 0;
			m.castling = BLACK_KINGSIDE_CASTLE_MOVE;
			m.enPas = false;
			m.promoteTo = BLACK_KING;
			quiet.push_back(m);
		}

		if (this->blackQueensideCastle && this->boardState[22] == EMPTY_SQUARE &&
			this->boardState[23] == EMPTY_SQUARE && this->boardState[24] == EMPTY_SQUARE &&
			this->boardState[21] == BLACK_ROOK &&
			!IsSquareAttacked(23, SIDE_WHITE) && !IsSquareAttacked(24, SIDE_WHITE) && !IsSquareAttacked(25, SIDE_WHITE))
		{
			m.score = 0;
			m.type = MOVE_QUIET_TYPE;
			m.to = 0;
			m.castling = BLACK_QUEENSIDE_CASTLE_MOVE;
			m.enPas = false;
			m.promoteTo = BLACK_KING;
			quiet.push_back(m);
		}

	}

	if (type == GEN_VIOLENT)
	{
		moves = violent;
	}
	else if (type == GEN_QUIET)
	{
		moves = quiet;
	}
	else // all
	{
		moves = violent;
		moves.insert(moves.end(), quiet.begin(), quiet.end());
	}
}

void Board::GenerateMoves(std::vector<MOVE>& moves, MOVEGEN_TYPE type, bool sort)
{
	std::vector<MOVE> temp;

	for (int r = 0; r < 8; ++r)
	{
		for (int f = 0; f < 8; ++f)
		{
			if (this->side == SIDE_WHITE)
			{
				switch (this->boardState[SquareTo120(r, f)])
				{
					case WHITE_KING:
						GenKingMoves(temp, r, f, SIDE_WHITE, type);
						if (temp.size() > 0)
						{
							moves.insert(moves.end(), temp.begin(), temp.end());
							temp.clear();
						}
						break;
					case WHITE_PAWN:
						GenPawnMoves(temp, r, f, SIDE_WHITE, type);
						if (temp.size() > 0)
						{
							moves.insert(moves.end(), temp.begin(), temp.end());
							temp.clear();
						}
						break;
					case WHITE_KNIGHT:
						GenKnightMoves(temp, r, f, SIDE_WHITE, type);
						if (temp.size() > 0)
						{
							moves.insert(moves.end(), temp.begin(), temp.end());
							temp.clear();
						}
						break;
					case WHITE_BISHOP:
						GenBishopMoves(temp, r, f, SIDE_WHITE, type);
						if (temp.size() > 0)
						{
							moves.insert(moves.end(), temp.begin(), temp.end());
							temp.clear();
						}
						break;
					case WHITE_ROOK:
						GenRookMoves(temp, r, f, SIDE_WHITE, type);
						if (temp.size() > 0)
						{
							moves.insert(moves.end(), temp.begin(), temp.end());
							temp.clear();
						}
						break;
					case WHITE_QUEEN:
						GenQueenMoves(temp, r, f, SIDE_WHITE, type);
						if (temp.size() > 0)
						{
							moves.insert(moves.end(), temp.begin(), temp.end());
							temp.clear();
						}
						break;
				}
			}
			else
			{
				switch (this->boardState[SquareTo120(r, f)])
				{
					case BLACK_KING:
						GenKingMoves(temp, r, f, SIDE_BLACK, type);
						if (temp.size() > 0)
						{
							moves.insert(moves.end(), temp.begin(), temp.end());
							temp.clear();
						}
						break;
					case BLACK_PAWN:
						GenPawnMoves(temp, r, f, SIDE_BLACK, type);
						if (temp.size() > 0)
						{
							moves.insert(moves.end(), temp.begin(), temp.end());
							temp.clear();
						}
						break;
					case BLACK_KNIGHT:
						GenKnightMoves(temp, r, f, SIDE_BLACK, type);
						if (temp.size() > 0)
						{
							moves.insert(moves.end(), temp.begin(), temp.end());
							temp.clear();
						}
						break;
					case BLACK_BISHOP:
						GenBishopMoves(temp, r, f, SIDE_BLACK, type);
						if (temp.size() > 0)
						{
							moves.insert(moves.end(), temp.begin(), temp.end());
							temp.clear();
						}
						break;
					case BLACK_ROOK:
						GenRookMoves(temp, r, f, SIDE_BLACK, type);
						if (temp.size() > 0)
						{
							moves.insert(moves.end(), temp.begin(), temp.end());
							temp.clear();
						}
						break;
					case BLACK_QUEEN:
						GenQueenMoves(temp, r, f, SIDE_BLACK, type);
						if (temp.size() > 0)
						{
							moves.insert(moves.end(), temp.begin(), temp.end());
							temp.clear();
						}
						break;
				}
			}
		}
	}

	if (sort)
	{
		std::sort(moves.begin(), moves.end(), [](const MOVE& a, const MOVE& b) { return a.score > b.score; });
	}

	moves = ExtractLegalMoves(moves);
}

MOVE Board::StringToMove(std::string moveStr)
{
	int fr = 8 - (moveStr[1] - '0');
	int ff = LetterToFile(moveStr[0]);
	int tr = 8 - (moveStr[3] - '0');
	int tf = LetterToFile(moveStr[2]);
	MOVE m;
	m.type = MOVE_QUIET_TYPE;
	m.from = SquareTo120(fr, ff);
	m.to = SquareTo120(tr, tf);
	m.castling = NO_CASTLING_MOVE;
	m.enPas = false;
	m.promoteTo = this->boardState[m.from];

	if (m.to == this->enPassantSquare)
	{
		m.enPas = true;
	}

	if (moveStr[4] != NULL)
	{
		switch (moveStr[4])
		{
		case 'n':
			if (this->side == SIDE_WHITE)
			{
				m.promoteTo = WHITE_KNIGHT;
			}
			else
			{
				m.promoteTo = BLACK_KNIGHT;
			}
			break;
		case 'b':
			if (this->side == SIDE_WHITE)
			{
				m.promoteTo = WHITE_BISHOP;
			}
			else
			{
				m.promoteTo = BLACK_BISHOP;
			}
			break;
		case 'r':
			if (this->side == SIDE_WHITE)
			{
				m.promoteTo = WHITE_ROOK;
			}
			else
			{
				m.promoteTo = BLACK_ROOK;
			}
			break;
		case 'q':
			if (this->side == SIDE_WHITE)
			{
				m.promoteTo = WHITE_QUEEN;
			}
			else
			{
				m.promoteTo = BLACK_QUEEN;
			}
			break;
		}
	}

	if (!strncmp(moveStr.c_str(), "e1g1", 4))
	{
		m.castling = WHITE_KINGSIDE_CASTLE_MOVE;
	}
	if (!strncmp(moveStr.c_str(), "e8g8", 4))
	{
		m.castling = BLACK_KINGSIDE_CASTLE_MOVE;
	}

	if (!strncmp(moveStr.c_str(), "e1c1", 4))
	{
		m.castling = WHITE_QUEENSIDE_CASTLE_MOVE;
	}
	if (!strncmp(moveStr.c_str(), "e8c8", 4))
	{
		m.castling = BLACK_QUEENSIDE_CASTLE_MOVE;
	}

	return m;
}

std::string Board::MoveToString(MOVE m)
{
	if (m.castling == WHITE_KINGSIDE_CASTLE_MOVE)
	{
		return "e1g1";
	}
	if (m.castling == BLACK_KINGSIDE_CASTLE_MOVE)
	{
		return "e8g8";
	}
	if (m.castling == WHITE_QUEENSIDE_CASTLE_MOVE)
	{
		return "e1c1";
	}
	if (m.castling == BLACK_QUEENSIDE_CASTLE_MOVE)
	{
		return "e8c8";
	}

	char fromFile;
	char toFile;
	int fromRank = 8 - SquareToRank64(m.from);
	int toRank = 8 - SquareToRank64(m.to);
	int promoteTo = m.promoteTo;
	char promChar;

	switch (SquareToFile64(m.from))
	{
		case 0:
			fromFile = 'a';
			break;
		case 1:
			fromFile = 'b';
			break;
		case 2:
			fromFile = 'c';
			break;
		case 3:
			fromFile = 'd';
			break;
		case 4:
			fromFile = 'e';
			break;
		case 5:
			fromFile = 'f';
			break;
		case 6:
			fromFile = 'g';
			break;
		case 7:
			fromFile = 'h';
			break;
		default:
			break;
	}

	switch (SquareToFile64(m.to))
	{
		case 0:
			toFile = 'a';
			break;
		case 1:
			toFile = 'b';
			break;
		case 2:
			toFile = 'c';
			break;
		case 3:
			toFile = 'd';
			break;
		case 4:
			toFile = 'e';
			break;
		case 5:
			toFile = 'f';
			break;
		case 6:
			toFile = 'g';
			break;
		case 7:
			toFile = 'h';
			break;
		default:
			break;
	}

	switch (abs(promoteTo))
	{
		case WHITE_KNIGHT:
			promChar = 'n';
			break;
		case WHITE_BISHOP:
			promChar = 'b';
			break;
		case WHITE_ROOK:
			promChar = 'r';
			break;
		case WHITE_QUEEN:
			promChar = 'q';
			break;
	}

	std::string moveStr;
	moveStr += fromFile;
	moveStr.append(std::to_string(fromRank));
	moveStr += toFile;
	moveStr.append(std::to_string(toRank));

	if (this->boardState[m.from] == WHITE_PAWN && toRank == 8)
	{
		moveStr += promChar;
	}
	if (this->boardState[m.from] == BLACK_PAWN && toRank == 1)
	{
		moveStr += promChar;
	}

	return moveStr;
}

void Board::DisplayMoves(std::vector<MOVE> moves)
{
	for (int i = 0; i < moves.size(); i++)
	{
		printf("move %d: %s\n", i, MoveToString(moves[i]).c_str());
	}
}

void Board::MakeMove(MOVE move)
{
	this->enPassantSquare = 0;
	if (move.castling == NO_CASTLING_MOVE)
	{
		if (move.enPas)
		{
			this->boardState[move.to] = move.promoteTo;
			this->boardState[move.from] = EMPTY_SQUARE;
			if (move.promoteTo == WHITE_PAWN)
			{
				this->boardState[move.to + 10] = EMPTY_SQUARE;
			}
			else
			{
				this->boardState[move.to - 10] = EMPTY_SQUARE;
			}
		}
		else // regular move
		{
			this->boardState[move.to] = move.promoteTo;
			this->boardState[move.from] = EMPTY_SQUARE;

			if (move.promoteTo == WHITE_PAWN || move.promoteTo == BLACK_PAWN)
			{
				if (abs(move.from - move.to) == 20) // set en passant square
				{
					if (move.from > 80 && move.from < 89) // white pawn
					{
						this->enPassantSquare = move.from - 10;
					}
					else // 1 black pawn
					{
						this->enPassantSquare = move.from + 10;
					}
				}
			}
			else if (move.promoteTo == WHITE_KING)
			{
				this->whiteKingsideCastle = false;
				this->whiteQueensideCastle = false;
			}
			else if (move.promoteTo == BLACK_KING)
			{
				this->blackKingsideCastle = false;
				this->blackQueensideCastle = false;
			}
			else if (move.from == 98 && move.promoteTo == WHITE_ROOK)
			{
				this->whiteKingsideCastle = false;
			}
			else if (move.from == 91 && move.promoteTo == WHITE_ROOK)
			{
				this->whiteQueensideCastle = false;
			}
			else if (move.from == 28 && move.promoteTo == BLACK_ROOK)
			{
				this->blackKingsideCastle = false;
			}
			else if (move.from == 21 && move.promoteTo == BLACK_ROOK)
			{
				this->blackQueensideCastle = false;
			}
		}
	}
	else // castling move
	{
		if (move.castling == WHITE_KINGSIDE_CASTLE_MOVE)
		{
			this->boardState[97] = WHITE_KING;
			this->boardState[96] = WHITE_ROOK;
			this->boardState[95] = EMPTY_SQUARE;
			this->boardState[98] = EMPTY_SQUARE;
			this->whiteKingsideCastle = false;
			this->whiteQueensideCastle = false;
		}
		else if (move.castling == WHITE_QUEENSIDE_CASTLE_MOVE)
		{
			this->boardState[93] = WHITE_KING;
			this->boardState[94] = WHITE_ROOK;
			this->boardState[95] = EMPTY_SQUARE;
			this->boardState[91] = EMPTY_SQUARE;
			this->whiteKingsideCastle = false;
			this->whiteQueensideCastle = false;
		}
		else if (move.castling == BLACK_KINGSIDE_CASTLE_MOVE)
		{
			this->boardState[27] = BLACK_KING;
			this->boardState[26] = BLACK_ROOK;
			this->boardState[25] = EMPTY_SQUARE;
			this->boardState[28] = EMPTY_SQUARE;
			this->blackKingsideCastle = false;
			this->blackQueensideCastle = false;
		}
		else // black queenside castle move
		{
			this->boardState[23] = BLACK_KING;
			this->boardState[24] = BLACK_ROOK;
			this->boardState[25] = EMPTY_SQUARE;
			this->boardState[21] = EMPTY_SQUARE;
			this->blackKingsideCastle = false;
			this->blackQueensideCastle = false;
		}
	}

	SwitchSide();
}

void Board::DisplayPv(std::vector<MOVE> pv)
{
	printf("pv");
	for (int i = 0; i < pv.size(); i++)
	{
		printf(" %s", MoveToString(pv[i]).c_str());
	}
	printf("\n");
}

std::vector<double> Board::ToTensor()
{
	std::vector<double> tensor;

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			tensor.push_back((double)this->boardState[SquareTo120(i, j)]);
		}
	}

	return tensor;
}

Board::Board()
{
	this->enPassantSquare = 0;
	this->side = SIDE_WHITE;
	this->whiteKingsideCastle = false;
	this->whiteQueensideCastle = false;
	this->blackKingsideCastle = false;
	this->blackQueensideCastle = false;
}

Board::~Board()
{
}
