#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>

// defines
#define ENGINE_NAME "fc0"
#define ENGINE_VERSION "68"
#define ENGINE_AUTHOR "nbq" //"nbqofficial <3 Pomid0ra"

#define WHITE_PAWN 10
#define WHITE_KNIGHT 30
#define WHITE_BISHOP 31
#define WHITE_ROOK 50
#define WHITE_QUEEN 90
#define WHITE_KING 1000
#define BLACK_PAWN -10
#define BLACK_KNIGHT -30
#define BLACK_BISHOP -31
#define BLACK_ROOK -50
#define BLACK_QUEEN -90
#define BLACK_KING -1000
#define EMPTY_SQUARE 0
#define NONE_SQUARE 404

#define NO_CASTLING_MOVE 0
#define WHITE_KINGSIDE_CASTLE_MOVE 1
#define WHITE_QUEENSIDE_CASTLE_MOVE 2
#define BLACK_KINGSIDE_CASTLE_MOVE 3
#define BLACK_QUEENSIDE_CASTLE_MOVE 4

#define MAX_INPUT_BUFFER 400*6

#define MAX_DEPTH 64
#define MAX_PROBABILITY 1000.0
#define PROBABILITY_LIMIT 0.0000001

#define NULL_MOVE_R 2

#define MCTS_WIN_FACTOR 1000
#define MCTS_DEPTH 8

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define WAC1 "2rr3k/pp3pp1/1nnqbN1p/3pN3/2pP4/2P3Q1/PPB4P/R4RK1 w - - 0 1" // Qg6
#define WAC2 "8/7p/5k2/5p2/p1p2P2/Pr1pPK2/1P1R3P/8 b - -"                  // Rxb2
#define WAC3 "5rk1/1ppb3p/p1pb4/6q1/3P1p1r/2P1R2P/PP1BQ1P1/5RKN w - -"     // Rg3

// MVVLVA SCORES
#define PxP 105
#define NxP 104
#define BxP 103
#define RxP 102
#define QxP 101
#define KxP 100

#define PxN 205
#define NxN 204
#define BxN 203
#define RxN 202
#define QxN 201
#define KxN 200

#define PxB 305
#define NxB 304
#define BxB 303
#define RxB 302
#define QxB 301
#define KxB 300

#define PxR 405
#define NxR 404
#define BxR 403
#define RxR 402
#define QxR 401
#define KxR 400

#define PxQ 505
#define NxQ 504
#define BxQ 503
#define RxQ 502
#define QxQ 501
#define KxQ 500

// structs
typedef struct _MOVE
{
	int score;
	int from;
	int to;
	int promoteTo;
	int castling;
	bool enPas;

}MOVE, * pMOVE;

typedef struct _SEARCHINFO
{
	int starttime;
	int stoptime;
	int depth;
	double probability;
	bool timeset;
	bool infinite;
	bool quit;
	bool stopped;
	float fh;
	float fhf;
	int nullCutoff;

}SEARCHINFO, * pSEARCHINFO;

// enums
enum SIDE { SIDE_WHITE, SIDE_BLACK, SIDE_NONE };

enum SEARCH_METHOD { METHOD_NEGAMAX, METHOD_PTS, METHOD_MCTS };

enum MOVEGEN_TYPE { GEN_ALL, GEN_VIOLENT, GEN_QUIET };

// consts
const int INF_SCORE = 900000;
const int MATE_SCORE = 300000;

const int KnightDir[8] = { -8, -19, -21, -12, 8, 19, 21, 12 };
const int RookDir[4] = { -1, -10, 1, 10 };
const int BishopDir[4] = { -9, -11, 11, 9 };
const int KingDir[8] = { -1, -10, 1, 10, -9, -11, 11, 9 };

const int PawnTable[64] = {
	0,	0,	0,	0,	0,	0,	0,	0,
	10,	10,	0,	-10,-10,0,	10,	10,
	5,	0,	0,	5,	5,	0,	0,	5,
	0,	0,	10,	20,	20,	10,	0,	0,
	5,	5,	5,	10,	10,	5,	5,	5,
	10,	10,	10,	20,	20,	10,	10,	10,
	20,	20,	20,	30,	30,	20,	20,	20,
	0,	0,	0,	0,	0,	0,	0,	0
};

const int KnightTable[64] = {
	0,	-10,0,	0,	0,	0,	-10,0,
	0,	0,	0,	5,	5,	0,	0,	0,
	0,	0,	10,	10,	10,	10,	0,	0,
	0,	0,	10,	20,	20,	10,	5,	0,
	5,	10,	15,	20,	20,	15,	10,	5,
	5,	10,	10,	20,	20,	10,	10,	5,
	0,	0,	5,	10,	10,	5,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0
};

const int BishopTable[64] = {
	0,	0,	-10,0,	0,	-10,0,	0,
	0,	0,	0,	10,	10,	0,	0,	0,
	0,	0,	10,	15,	15,	10,	0,	0,
	0,	10,	15,	20,	20,	15,	10,	0,
	0,	10,	15,	20,	20,	15,	10,	0,
	0,	0,	10,	15,	15,	10,	0,	0,
	0,	0,	0,	10,	10,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0
};

const int RookTable[64] = {
	0,	0,	5,	10,	10,	5,	0,	0,
	0,	0,	5,	10,	10,	5,	0,	0,
	0,	0,	5,	10,	10,	5,	0,	0,
	0,	0,	5,	10,	10,	5,	0,	0,
	0,	0,	5,	10,	10,	5,	0,	0,
	0,	0,	5,	10,	10,	5,	0,	0,
	25,	25,	25,	25,	25,	25,	25,	25,
	0,	0,	5,	10,	10,	5,	0,	0
};

const int Mirror64[64] = {
	56,	57,	58,	59,	60,	61,	62,	63,
	48,	49,	50,	51,	52,	53,	54,	55,
	40,	41,	42,	43,	44,	45,	46,	47,
	32,	33,	34,	35,	36,	37,	38,	39,
	24,	25,	26,	27,	28,	29,	30,	31,
	16,	17,	18,	19,	20,	21,	22,	23,
	8,	9,	10,	11,	12,	13,	14,	15,
	0,	1,	2,	3,	4,	5,	6,	7
};

// externs
extern int ranks64[120];
extern int files64[120];
extern HANDLE hConsoleOut;
extern HANDLE hConsoleIn;
extern SEARCHINFO searchInfo;

