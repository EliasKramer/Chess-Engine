#pragma once
#include "Player.h"
#include <iostream>
class HumanPlayer : public Player
{
	HumanPlayer();
	Move getNextMove(std::vector<Move*> possibleMoves) override;
};