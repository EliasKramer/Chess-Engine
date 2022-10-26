#include "Move.h"

Move::Move(Square givenStart, Square givenDest) :
	_start(givenStart),
	_destination(givenDest)
{}

const Square Move::getStart()
{
	return _start;
}

const Square Move::getDestination()
{
	return _destination;
}

void Move::execute(BoardRepresentation& board)
{
	board.copySquareToPos(_start, _destination);
	board.delAtPos(_start);
}

BitBoard Move::getBBWithMoveDone()
{
	return BB_SQUARE[_start] | BB_SQUARE[_destination];
}

const std::string Move::getString()
{
	return SQUARE_STRING[_start] + SQUARE_STRING[_destination];
}

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
