#pragma once
#include "Move.h"
class MoveEnPassant : public Move
{
private:
	Coordinate coordToRemovePiece;
public:
	MoveEnPassant();
	MoveEnPassant(
		Coordinate givenStart,
		Coordinate givenDestination,
		Coordinate givenCoordToRemovePiece);

	void execute(
		std::function<ChessPiece(Coordinate)> getAtPosition,
		std::function<void(ChessPiece, Coordinate)> setPieceAt) override;

	Coordinate getCoordToRemove();
};