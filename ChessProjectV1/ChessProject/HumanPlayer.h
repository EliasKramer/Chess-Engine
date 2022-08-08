#pragma once
#include "Player.h"
#include "MovePawnPromotion.h"
#include <iostream>
class HumanPlayer : public Player
{
public:
	HumanPlayer();
	std::unique_ptr<Move> getNextMove(std::vector<std::unique_ptr<Move>> possibleMoves) override;
};