#pragma once

#include "valuenet.h"

class Training
{
	private:

		std::vector<Board> boardHistory;
		int cnt = 0;

	public:

		ValueNet vn;

		void LoadBoardsFromFile(std::string fileName);

		void ProcessGame(std::string fileName);

		void Train(std::string folderName, int numOfGames);

		void Execute(int epochs);

		Training();

		~Training();

};