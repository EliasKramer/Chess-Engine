#include "TestMethods.h"
bool containsMove(const std::list<Move>& list, Move x)
{
	return std::find(list.begin(), list.end(), x) != list.end();
}