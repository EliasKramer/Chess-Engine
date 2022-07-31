#pragma once
#include "Player.h"
#include "MovePawnPromotion.h"
#include <iostream>
class HumanPlayer : public Player
{
public:
	HumanPlayer();
	Move* getNextMove(std::vector<Move*> possibleMoves) override;
};