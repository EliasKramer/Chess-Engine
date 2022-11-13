#pragma once
#include "Player.h"
#include <iostream>

class HumanPlayer : public Player
{
public:
	HumanPlayer();
	HumanPlayer(std::string name);
	

	int get_move(const ChessBoard& board, const MoveList& moves) override;
};