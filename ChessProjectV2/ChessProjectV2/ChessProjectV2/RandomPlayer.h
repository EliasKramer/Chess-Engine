#pragma once
#include "Player.h"
#include <random>

class RandomPlayer : public Player
{
public:
	int getMove(ChessBoard& board, UniqueMoveList& moves) override;
};

