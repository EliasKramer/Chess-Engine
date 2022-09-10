#pragma once
#include "Player.h"
#include <iostream>

class HumanPlayer : public Player
{
public:
	int getMove(ChessBoard& board, UniqueMoveList& moves) override;
};

