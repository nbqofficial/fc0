#include "chess.h"

Chess::Chess()
{
	RanksFiles64Init();
	uci.UciLoop();
}

Chess::~Chess()
{
}
