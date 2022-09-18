#pragma once
#include "Move.h"
#include "ChessBoard.h"
class Player
{
public:
	//returns the index of the move in the list
	virtual int getMove(const ChessBoard& board, const UniqueMoveList& moves);
};