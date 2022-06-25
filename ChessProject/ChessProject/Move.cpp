#include "Move.h"

Move::Move()
{
	start = Coordinate();
	destination = Coordinate();
	piece = nullptr;
}

Move::Move(ChessPiece* givenPiece,
	Coordinate* givenStart,
	Coordinate* givenDestination)
{
	piece = givenPiece;
	start = *givenStart;
	destination = *givenDestination;
}

Coordinate* Move::getStart()
{
	return &start;
}

Coordinate* Move::getDestination()
{
	return &destination;
}

ChessPiece* Move::getPiece()
{
	return piece;
}

bool Move::isValid()
{
	return
		start.isValid() &&
		destination.isValid() &&
		start != destination &&
		piece != nullptr && piece->isValid();
}