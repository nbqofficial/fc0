#include "uci.h"

void UCI::Go(char* lineIn)
{
	int depth = -1;
	int movestogo = 30;
	int movetime = -1;
	int time = -1;
	int inc = 0;
	char* ptr = NULL;
	searchInfo.timeset = false;

	if ((ptr = strstr(lineIn, "infinite")))
	{
		; // do nothing
	}

	if ((ptr = strstr(lineIn, "binc")) && board.GetSide() == SIDE_BLACK)
	{
		inc = atoi(ptr + 5);
	}
	if ((ptr = strstr(lineIn, "winc")) && board.GetSide() == SIDE_WHITE)
	{
		inc = atoi(ptr + 5);
	}

	if ((ptr = strstr(lineIn, "btime")) && board.GetSide() == SIDE_BLACK)
	{
		time = atoi(ptr + 6);
	}
	if ((ptr = strstr(lineIn, "wtime")) && board.GetSide() == SIDE_WHITE)
	{
		time = atoi(ptr + 6);
	}

	if ((ptr = strstr(lineIn, "movestogo")))
	{
		movestogo = atoi(ptr + 10);
	}

	if ((ptr = strstr(lineIn, "movetime")))
	{
		movetime = atoi(ptr + 9);
	}

	if ((ptr = strstr(lineIn, "depth")))
	{
		depth = atoi(ptr + 6);
	}

	if (movetime != -1)
	{
		time = movetime;
		movestogo = 1;
	}

	searchInfo.starttime = GetTimeMs();
	searchInfo.depth = depth;
	searchInfo.probability = depth;

	if (time != -1)
	{
		searchInfo.timeset = true;
		time /= movestogo;
		time -= 50;
		searchInfo.stoptime = searchInfo.starttime + time + inc;
	}

	if (depth == -1)
	{
		searchInfo.depth = MAX_DEPTH;
		searchInfo.probability = MAX_PROBABILITY;
	}

	MOVE bestMove = search.SearchPosition(board, searchInfo.depth, searchInfo.probability, METHOD_PTS);
	std::string moveStr = board.MoveToString(bestMove);
	board.MakeMove(bestMove);

	printf("bestmove %s\n", moveStr.c_str());
}

void UCI::Position(char* lineIn)
{
	lineIn += 9;
	char* ptrChar = lineIn;

	if (strncmp(lineIn, "startpos", 8) == 0)
	{
		board.Init(START_FEN);
	}
	else
	{
		ptrChar = strstr(lineIn, "fen");
		if (ptrChar == NULL)
		{
			board.Init(START_FEN);
		}
		else
		{
			ptrChar += 4;
			board.Init(ptrChar);
		}
	}

	ptrChar = strstr(lineIn, "moves");

	if (ptrChar != NULL)
	{
		ptrChar += 6;
		while (*ptrChar)
		{
			std::string move;
			while (*ptrChar && *ptrChar != ' ')
			{
				move += ptrChar;
				ptrChar++;
			}
			board.MakeMove(board.StringToMove(move));
			move.clear();
			ptrChar++;
		}
	}
}

void UCI::UciLoop()
{
	setvbuf(stdin, NULL, _IONBF, BUFSIZ);
	setvbuf(stdout, NULL, _IONBF, BUFSIZ);

	char line[MAX_INPUT_BUFFER];

	printf("id name %s\n", ENGINE_NAME);
	printf("id author %s\n", ENGINE_AUTHOR);
	printf("uciok\n");

	while (1)
	{
		memset(&line[0], 0, sizeof(line));
		fflush(stdout);

		if (!fgets(line, MAX_INPUT_BUFFER, stdin)) { continue; }

		if (line[0] == '\n') { continue; }

		if (!strncmp(line, "isready", 7))
		{
			printf("readyok\n");
			continue;
		}
		else if (!strncmp(line, "position", 8))
		{
			Position(line);
		}
		else if (!strncmp(line, "ucinewgame", 10))
		{
			Position((char*)"position startpos\n");
		}
		else if (!strncmp(line, "go", 2))
		{
			Go(line);
		}
		else if (!strncmp(line, "quit", 4))
		{
			exit(EXIT_SUCCESS);
			break;
		}
		else if (!strncmp(line, "uci", 3))
		{
			printf("id name %s\n", ENGINE_NAME);
			printf("id author %s\n", ENGINE_AUTHOR);
			printf("uciok\n");
		}
		else if (!strncmp(line, "perft", 5))
		{
			perft.Check(board, 5);
		}
		else if (!strncmp(line, "train", 5))
		{
			training.Execute(3);
		}
	}
}
