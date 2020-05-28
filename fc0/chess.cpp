#include "chess.h"
#include "mcts.h"

Chess::Chess()
{
	RanksFiles64Init();
	uci.UciLoop();
}

Chess::~Chess()
{
}
