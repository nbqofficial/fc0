#pragma once

#include "definitions.h"

int GetTimeMs();

int SquareTo120(int rank, int file);

void RanksFiles64Init();

int SquareToRank64(int square);

int SquareToFile64(int square);

int LetterToFile(char letter);

bool AreBoardsEqual(std::vector<int> b1, std::vector<int> b2);

int InputWaiting();

void StopEngine(bool* stopped);

void ClearSearchInfo();

void CheckUp();