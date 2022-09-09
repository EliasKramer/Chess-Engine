#include "MovePromote.h"

MovePromote::MovePromote(Square givenStart, Square givenDest, ChessPiece promotingPiece)
	:Move(givenStart, givenDest),
	_promotingPiece(promotingPiece)
{}

void MovePromote::execute(std::function<void(Square, Square)> copySquare,
	std::function<void(ChessPiece, Square)> setAtPos,
	std::function<void(Square)> delAtPos)
{
	delAtPos(_start);
	delAtPos(_destination);
	setAtPos(_promotingPiece, _destination);
}