#include "MoveEnPassant.h"
MoveEnPassant::MoveEnPassant() : Move()
{}

MoveEnPassant::MoveEnPassant(
	Coordinate* givenStart,
	Coordinate* givenDestination,
	Coordinate givenCoordToRemovePiece)
	: Move(givenStart, givenDestination), //calling base class constructor
	coordToRemovePiece(givenCoordToRemovePiece) //initializing member variable
{}

void MoveEnPassant::execute(
	std::function<ChessPiece(Coordinate*)> getAtPosition,
	std::function<void(ChessPiece*, Coordinate*)> setPieceAt)
{
	Move::execute(getAtPosition, setPieceAt);
	ChessPiece emptyPiece = ChessPiece();
	setPieceAt(&emptyPiece, &coordToRemovePiece);
}

Coordinate MoveEnPassant::getCoordToRemove()
{
	return coordToRemovePiece;
}