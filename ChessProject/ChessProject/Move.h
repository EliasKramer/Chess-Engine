#pragma once
#include "ChessPiece.h"
#include "Coordinate.h"
class Move
{
private:
	Coordinate start;
	Coordinate destination;
	ChessPiece* piece;
public:
	Move(ChessPiece* givenPiece,
		Coordinate* givenStart,
		Coordinate* givenDestination);
};

