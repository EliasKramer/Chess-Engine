#include "Move.h"

Move::Move(Square givenStart, Square givenDest):
	_start(givenStart),
	_destination(givenDest)
{}

Square Move::getStart()
{
	return _start;
}

Square Move::getDestination()
{
	return _destination;
}
/*
void Move::execute(
	std::function<void(Square, Square)> copySquare,
	std::function<void(ChessPiece, Square)> setAtPos,
	std::function<void(Square)> delAtPos,
	std::function<void(Square)> setEnPassant)
{
	copySquare(_start, _destination);
	delAtPos(_start);
}

Square* Move::getAtPosWithMoveDone(Square pos)
{
	//TODO
	return nullptr;
}
*/
bool operator==(const Move& first, const Move& second)
{
	return 
		first._destination == second._destination &&
		first._start == second._start;
}

bool operator!=(const Move& first, const Move& second)
{
	return !(first == second);
}
