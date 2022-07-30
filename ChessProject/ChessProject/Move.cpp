#include "Move.h"

Move::Move()	
{}

Move::Move(
	Coordinate givenStart,
	Coordinate givenDestination) :
	start(givenStart),
	destination(givenDestination)
{}

Move::~Move()
{
}

Coordinate Move::getStart()
{
	return start;
}

Coordinate Move::getDestination()
{
	return destination;
}

bool Move::isValid()
{
	return
		start.isValid() &&
		destination.isValid() &&
		start != destination;
}

void Move::execute(
	std::function<ChessPiece(Coordinate)> getAtPosition,
	std::function<void(ChessPiece, Coordinate)> setPieceAt)
{
	ChessPiece startPiece = getAtPosition(start);
	ChessPiece emptyPiece = ChessPiece();
	if (isValid())
	{
		setPieceAt(emptyPiece, start);
		setPieceAt(startPiece, destination);
	}
}

bool Move::operator==(const Move& other) const
{
	return start == other.start && destination == other.destination;
}

bool Move::operator!=(const Move& other) const
{
	return !(operator ==(other));
}
