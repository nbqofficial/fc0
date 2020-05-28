#include "chess.h"

int main()
{
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	Chess chess;

	CloseHandle(hConsoleOut);
	CloseHandle(hConsoleIn);

	return 0;
}