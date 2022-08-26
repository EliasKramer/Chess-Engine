#include "TypeOnSquare.h"

PieceTypeOnSquare::PieceTypeOnSquare(Square pos, PieceType type)
	:_pos(pos),
	_chessType(type)
{}

Square PieceTypeOnSquare::getPos() const
{
	return _pos;
}

PieceType PieceTypeOnSquare::getType() const
{
	return _chessType;
}