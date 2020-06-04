#include "chess.h"

int main()
{
	srand(unsigned(time(0)));

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	Chess chess;

	CloseHandle(hConsoleOut);
	CloseHandle(hConsoleIn);

	return 0;
}