#pragma once
#include "Move.h"
#include "ChessPiece.h"
class MovePromote : public Move
{
private:
	PieceType _promotingType;
public:
	MovePromote(Square givenStart, Square givenDest, PieceType promotingType);
};