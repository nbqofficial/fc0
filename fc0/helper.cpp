#include "helper.h"

int ranks64[120];
int files64[120];

HANDLE hConsoleOut;
HANDLE hConsoleIn;

SEARCHINFO searchInfo;

int GetTimeMs()
{
	return GetTickCount();
}

int SquareTo120(int rank, int file)
{
	return ((21 + (file)) + ((rank) * 10));
}

void RanksFiles64Init()
{
	for (int i = 0; i < 120; i++)
	{
		ranks64[i] = NONE_SQUARE;
		files64[i] = NONE_SQUARE;
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int sq = SquareTo120(i, j);
			ranks64[sq] = i;
			files64[sq] = j;
		}
	}
}

int SquareToRank64(int square)
{
	return ranks64[square];
}

int SquareToFile64(int square)
{
	return files64[square];
}

int LetterToFile(char letter)
{
	int file = 0;
	switch (letter)
	{
	case 'a':
		file = 0;
		break;
	case 'b':
		file = 1;
		break;
	case 'c':
		file = 2;
		break;
	case 'd':
		file = 3;
		break;
	case 'e':
		file = 4;
		break;
	case 'f':
		file = 5;
		break;
	case 'g':
		file = 6;
		break;
	case 'h':
		file = 7;
		break;
	default:
		file = 0;
		break;
	}
	return file;
}

int InputWaiting()
{
	static int init = 0, pipe;
	DWORD dw;

	if (!init)
	{
		init = 1;
		pipe = !GetConsoleMode(hConsoleIn, &dw);
		if (!pipe)
		{
			SetConsoleMode(hConsoleIn, dw & ~(ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT));
			FlushConsoleInputBuffer(hConsoleIn);
		}
	}
	if (pipe)
	{
		if (!PeekNamedPipe(hConsoleIn, NULL, 0, NULL, &dw, NULL))
		{
			return 1;
		}
		return dw;
	}
	else
	{
		GetNumberOfConsoleInputEvents(hConsoleIn, &dw);
		return dw <= 1 ? 0 : dw;
	}
}

void StopEngine(bool* stopped)
{
	if (InputWaiting())
	{
		*stopped = true;
		char line[MAX_INPUT_BUFFER];
		if (fgets(line, MAX_INPUT_BUFFER, stdin))
		{
			if (!strncmp(line, "quit", 4))
			{
				exit(EXIT_SUCCESS);
			}
		}
	}
}

void ClearSearchInfo()
{
	searchInfo.starttime = 0;
	searchInfo.stoptime = 0;
	searchInfo.depth = -1;
	searchInfo.probability = 1.0;
	searchInfo.timeset = false;
	searchInfo.infinite = false;
	searchInfo.quit = false;
	searchInfo.stopped = false;
	searchInfo.fh = 0.0;
	searchInfo.fhf = 0.0;
	searchInfo.nullCutoff = 0;
}

void CheckUp()
{
	if (searchInfo.timeset && GetTimeMs() > searchInfo.stoptime)
	{
		searchInfo.stopped = true;
	}
	StopEngine(&searchInfo.stopped);
}
