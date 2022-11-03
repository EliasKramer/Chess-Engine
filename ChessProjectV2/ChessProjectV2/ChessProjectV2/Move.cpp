#include "Move.h"

Move::Move(Square givenStart, Square givenDest, MoveFlag flag) :
	_start(givenStart),
	_destination(givenDest),
	_flag(flag)
{}

Square Move::getStart() const
{
	return _start;
}

Square Move::getDestination() const
{
	return _destination;
}

void Move::execute(BoardRepresentation& board)
{
	board.copySquareToPos(_start, _destination);
	board.delAtPos(_start);
}

std::string Move::getString() const
{
	return SQUARE_STRING[_start] + SQUARE_STRING[_destination];
}

bool operator==(const Move& first, const Move& second)
{
	return
		first._destination == second._destination &&
		first._start == second._start && 
		first._flag == second._flag;
}

bool operator!=(const Move& first, const Move& second)
{
	return !(first == second);
}
