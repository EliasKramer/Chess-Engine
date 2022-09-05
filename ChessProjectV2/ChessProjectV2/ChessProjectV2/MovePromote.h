#pragma once
#include "Move.h"
#include "ChessPiece.h"
class MovePromote : public Move
{
private:
	ChessPiece _promotingPiece;
public:
	MovePromote(Square givenStart, Square givenDest, ChessPiece promotingPiece);

	void execute(
		std::function<void(Square, Square)> copySquare,
		std::function<void(ChessPiece, Square)> setAtPos,
		std::function<void(Square)> delAtPos) override;

	//no overriding of getBBWithMoveDone, because it acts the same as the normal move
};