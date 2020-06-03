#include "training.h"

void Training::LoadBoardsFromFile(std::string fileName)
{
	std::ifstream file(fileName);
	if (file.is_open())
	{
		std::string fen;
		while (std::getline(file, fen))
		{
			Board temp;
			temp.Init(fen);
			boardHistory.push_back(temp);
		}
		file.close();
	}
}

void Training::ProcessGame(std::string fileName)
{
	LoadBoardsFromFile(fileName);
	for (int i = 0; i < boardHistory.size(); i++)
	{
		cnt++;
		vn.Evaluate(boardHistory[i], true, {tanh(boardHistory[i].EvaluateInt())});
	}
	boardHistory.clear();
}

void Training::Train(std::string folderName, int numOfGames)
{
	std::string filePath;
	for (int i = 0; i < numOfGames; i++)
	{
		filePath.clear();
		filePath.append(folderName);
		filePath.append("/");
		filePath.append(std::to_string(i));
		filePath.append(".txt");
		SetConsoleTextAttribute(hConsoleOut, 0xC);
		printf("TRAINING FILE: %s\n", filePath.c_str());
		SetConsoleTextAttribute(hConsoleOut, 0x7);
		ProcessGame(filePath);
		printf("Error: %f\n", vn.GetError());
	}
}

void Training::Execute(int epochs)
{
	for (int i = 0; i < epochs; i++)
	{
		Train("GamesWhite", 150);

		Train("GamesBlack", 150);

		Train("GamesDrawn", 100);
	}
	vn.~ValueNet();
}

Training::Training()
{
	printf("Training Init()\n");
}

Training::~Training()
{
}
