#include "Move.h"

Move::Move(Square givenStart, Square givenDest, MoveFlag flag) :
	_start(givenStart),
	_destination(givenDest),
	_flag(flag),
	_colorOfPiece(ChessColor::NoColor)
{
	if ((flag == Normal ||
		flag == EnPassant) == false)
	{
		throw std::invalid_argument("Invalid flag for move (False constructor called)");
	}
}

Move::Move(
	Square givenStart,
	Square givenDest,
	ChessColor color,
	MoveFlag flag) :
	_start(givenStart),
	_destination(givenDest),
	_flag(flag),
	_colorOfPiece(color)
{
	if ((flag == MoveFlag::PromoteQueen ||
		flag == MoveFlag::PromoteRook ||
		flag == MoveFlag::PromoteBishop ||
		flag == MoveFlag::PromoteKnight) == false)
	{
		throw std::invalid_argument("Invalid flag for move (False constructor called)");
	}
}

Move::Move(ChessColor col, CastlingType castleType) :
	_start(SQUARE_NONE),
	_destination(SQUARE_NONE),
	_flag(Castle),
	_colorOfPiece(col)
{
	if (_flag != Castle)
	{
		throw std::invalid_argument("Invalid flag for move (False constructor called)");
	}

	_start = START_SQUARE_KING_CASTLING[col];
	_destination = DESTINATION_SQUARE_KING_CASTLING[col][castleType];
}

Square Move::getStart() const
{
	return _start;
}

Square Move::getDestination() const
{
	return _destination;
}

MoveFlag Move::getFlag() const
{
	return _flag;
}

void Move::execute(BoardRepresentation& board) const
{
	//TODO Implement getting castling squares
	board.copySquareToPos(_start, _destination);
	board.delAtPos(_start);
}

std::string Move::getString() const
{	
	if (_flag == Castle)
	{
		return CASTLE_STRING_FOR_DESTINATION.at(_destination);
	}

	return SQUARE_STRING[_start] + 
		SQUARE_STRING[_destination] + 
		MOVE_FLAG_STRING.at(_flag);
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