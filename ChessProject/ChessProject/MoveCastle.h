#pragma once
#include "Move.h"
class MoveCastle : public Move
{
private:
	Move secondMove;
public:
	MoveCastle();
	MoveCastle(
		Coordinate* givenStart,
		Coordinate* givenDestination,
		Move givenSecondMove);

	void execute(
		std::function<ChessPiece(Coordinate*)> getAtPosition,
		std::function<void(ChessPiece*, Coordinate*)> setPieceAt) override;

	Move getSecondMove();
};

