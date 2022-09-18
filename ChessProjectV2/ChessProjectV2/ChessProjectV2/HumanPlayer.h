#pragma once
#include "Player.h"
#include <iostream>

class HumanPlayer : public Player
{
public:
	int getMove(const ChessBoard& board, const UniqueMoveList& moves) override;
};