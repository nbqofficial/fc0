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
#define ENGINE_VERSION "55"
#define ENGINE_AUTHOR "nbqofficial"

#define WHITE_PAWN 1
#define WHITE_KNIGHT 3
#define WHITE_BISHOP 4
#define WHITE_ROOK 5
#define WHITE_QUEEN 9
#define WHITE_KING 100
#define BLACK_PAWN -1
#define BLACK_KNIGHT -3
#define BLACK_BISHOP -4
#define BLACK_ROOK -5
#define BLACK_QUEEN -9
#define BLACK_KING -100
#define EMPTY_SQUARE 0
#define NONE_SQUARE 404

#define NO_CASTLING_MOVE 0
#define WHITE_KINGSIDE_CASTLE_MOVE 1
#define WHITE_QUEENSIDE_CASTLE_MOVE 2
#define BLACK_KINGSIDE_CASTLE_MOVE 3
#define BLACK_QUEENSIDE_CASTLE_MOVE 4

#define MOVE_VIOLENT_TYPE 0
#define MOVE_QUIET_TYPE 1

#define MAX_INPUT_BUFFER 400*6

#define MAX_DEPTH 64
#define MAX_PROBABILITY 1000.0
#define PROBABILITY_LIMIT 0.0000001

#define NULL_MOVE_R 2

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define WAC1 "2rr3k/pp3pp1/1nnqbN1p/3pN3/2pP4/2P3Q1/PPB4P/R4RK1 w - - 0 1" // Qg6
#define WAC2 "8/7p/5k2/5p2/p1p2P2/Pr1pPK2/1P1R3P/8 b - -" // Rxb2
#define WAC3 "5rk1/1ppb3p/p1pb4/6q1/3P1p1r/2P1R2P/PP1BQ1P1/5RKN w - -" // Rg3

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
	int type;
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

enum SEARCH_METHOD { METHOD_NEGAMAX, METHOD_PTS };

enum MOVEGEN_TYPE { GEN_ALL, GEN_VIOLENT, GEN_QUIET };

// consts
const double INF_SCORE = 90000.0;
const double MATE_SCORE = 30000.0;

const int KnightDir[8] = { -8, -19, -21, -12, 8, 19, 21, 12 };
const int RookDir[4] = { -1, -10, 1, 10 };
const int BishopDir[4] = { -9, -11, 11, 9 };
const int KingDir[8] = { -1, -10, 1, 10, -9, -11, 11, 9 };

// externs
extern int ranks64[120];
extern int files64[120];
extern HANDLE hConsoleOut;
extern HANDLE hConsoleIn;
extern SEARCHINFO searchInfo;


/*
startpos:
depth: 1 score: 6 nodes: 20 pv: d2d3 mo: -nan nc: 0
depth: 2 score: 0 nodes: 156 pv: d2d3 d7d6 mo: 0.47 nc: 0
depth: 3 score: 5 nodes: 2366 pv: g1f3 d7d6 d2d3 mo: 0.29 nc: 0
depth: 4 score: 0 nodes: 8881 pv: d2d3 b8c6 g1f3 e7e6 mo: 0.36 nc: 41
depth: 5 score: 3 nodes: 83867 pv: d2d3 b8c6 b1c3 e7e6 g1f3 mo: 0.36 nc: 519
depth: 6 score: 1 nodes: 411662 pv: e2e4 g8f6 e4e5 f6d5 d2d4 d7d6 mo: 0.45 nc: 2893

wac1:
depth 1: score: -1988 nodes: 895 pv: f6g4 mo: -nan nc: 0
depth 2: score: -1992 nodes: 4921 pv: f6g4 c8c7 mo: 0.82 nc: 0
depth 3: score: -1992 nodes: 18464 pv: f6g4 f7f6 e5g6 mo: 0.86 nc:0
depth 4: score: 29938 nodes: 125092 pv: g3g6 c6d4 g6h7 mo: 0.93 nc: 36
depth 5: score: 29939 nodes: 615370 pv: g3g6 c6d4 g6h7 mo: 0.95 nc: 374
depth 6: score: 29940 nodes: 3859481 pv: g3g6 c6d4 g6h7 mo: 0.96 nc: 3885
*/