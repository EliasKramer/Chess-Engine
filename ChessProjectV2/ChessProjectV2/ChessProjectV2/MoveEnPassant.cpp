#include "MoveEnPassant.h"

MoveEnPassant::MoveEnPassant(Square givenStart, Square givenDest, Square posToDel)
	: Move(givenStart, givenDest),
	_posToDel(posToDel)
{}

void MoveEnPassant::execute(
	std::function<void(Square, Square)> copySquare,
	std::function<void(ChessPiece, Square)> setAtPos,
	std::function<void(Square)> delAtPos)
{
	Move::execute(copySquare, setAtPos, delAtPos);
	delAtPos(_posToDel);
}

BitBoard MoveEnPassant::getBBWithMoveDone()
{
	return BB_SQUARE[_posToDel] | BB_SQUARE[_destination] | BB_SQUARE[_start];
}
