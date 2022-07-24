#include "TestMethods.h"
bool containsMove(const std::vector<Move*>& list, Move* x)
{
	//return false;
	for (Move* move : list)
	{
		if(*move == *x)
		{
			return true;
		}
	}
	return false;
	//return std::find(list.begin(), list.end(), x) != list.end();
}