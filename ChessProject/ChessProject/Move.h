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
	Move();
	Move(ChessPiece* givenPiece,
		Coordinate* givenStart,
		Coordinate* givenDestination);
	Coordinate* getStart();
	Coordinate* getDestination();
	ChessPiece* getPiece();
	bool isValid();
};