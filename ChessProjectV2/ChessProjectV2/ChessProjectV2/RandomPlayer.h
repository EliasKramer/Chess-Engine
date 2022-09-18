#pragma once
#include "Player.h"
#include <random>

class RandomPlayer : public Player
{
public:
	int getMove(const ChessBoard& board, const UniqueMoveList& moves) override;
};

