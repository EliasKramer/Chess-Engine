#include "Move.h"

Move::Move(Square givenStart, Square givenDest, PieceType type):
	_delSquares(std::vector<Square>()),
	_piecesToSet(std::vector<PieceTypeOnSquare>())
{
	_delSquares.push_back(givenStart);
	_piecesToSet.push_back(PieceTypeOnSquare(givenDest, type));
}

Square Move::getStart()
{
	return _delSquares.front();
}

Square Move::getDestination()
{
	return _piecesToSet.front().getPos();
}

PieceType Move::getTypeAtDest()
{
	return _piecesToSet.front().getType();
}

void Move::addDeletionSquare(Square square)
{
	_delSquares.push_back(square);
}

void Move::addPieceToSetAt(Square position, PieceType type)
{
	_piecesToSet.push_back(PieceTypeOnSquare(position, type));
}

bool operator==(const Move& first, const Move& second)
{
	return 
		first._piecesToSet.front().getPos() == second._piecesToSet.front().getPos() &&
		first._piecesToSet.front().getType() == second._piecesToSet.front().getType() &&
		first._delSquares.front() == second._delSquares.front();
}

bool operator!=(const Move& first, const Move& second)
{
	return !(first == second);
}
