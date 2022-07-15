#include "TestMethods.h"
bool containsMove(const std::vector<Move>& list, Move* x)
{
	return std::find(list.begin(), list.end(), *x) != list.end();
}

void testGetAtPositionWtihMoveDoneKingMoves(ChessColor* col)
{
}
