#pragma once
#include "Move.h"
#include <vector>
#include <memory>
class Player
{
public:
	Player();
	virtual std::unique_ptr<Move> getNextMove(std::vector<std::unique_ptr<Move>> possibleMoves);
};