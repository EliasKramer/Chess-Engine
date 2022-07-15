#pragma once
#include "ChessPiece.h"
#include "Coordinate.h"
class Move
{
private:
	Coordinate start;
	Coordinate destination;
public:
	Move();
	Move(Coordinate* givenStart,
		Coordinate* givenDestination);
	Coordinate getStart();
	Coordinate getDestination();
	bool isValid();
	bool operator ==(const Move& other) const;
	bool operator !=(const Move& other) const;
};