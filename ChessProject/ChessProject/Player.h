#pragma once
#include "Move.h"
#include <vector>
class Player
{
public:
	Player();
	virtual Move* getNextMove(std::vector<Move*> possibleMoves);
};

