#pragma once
#include "Move.h"
#include "ChessBoard.h"
class Player
{
public:
	//returns the index of the move in the list
	virtual int getMove(ChessBoard& board, UniqueMoveList& moves);
};