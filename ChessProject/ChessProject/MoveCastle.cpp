#include "MoveCastle.h"

MoveCastle::MoveCastle() : Move()
{}

MoveCastle::MoveCastle(
	Coordinate* givenStart,
	Coordinate* givenDestination,
	Move givenSecondMove) 
	: Move(givenStart, givenDestination),
	secondMove(givenSecondMove)
{}

void MoveCastle::execute(
	std::function<ChessPiece(Coordinate*)> getAtPosition,
	std::function<void(ChessPiece*, Coordinate*)> setPieceAt)
{
	Move::execute(getAtPosition, setPieceAt);
	secondMove.execute(getAtPosition, setPieceAt);
}

Move MoveCastle::getSecondMove()
{
	return secondMove;
}
