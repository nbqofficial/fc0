#pragma once

#include "definitions.h"

int GetTimeMs();

int SquareTo120(int rank, int file);

int SquareTo64(int rank, int file);

void RanksFiles64Init();

int MirrorBoard(int square);

int SquareToRank64(int square);

int SquareToFile64(int square);

int LetterToFile(char letter);

char FileToLetter(int file);

int RandomFunc(int j);

int InputWaiting();

void StopEngine(bool* stopped);

void ClearSearchInfo();

void CheckUp();