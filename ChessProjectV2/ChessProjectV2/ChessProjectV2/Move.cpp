#include "Move.h"

Move::Move(Square given_start, Square given_dest, MoveFlag flag) :
	_start(given_start),
	_destination(given_dest),
	_flag(flag),
	_color_of_piece(ChessColor::no_color)
{
	if ((flag == normal ||
		flag == en_passant) == false)
	{
		throw std::invalid_argument("Invalid flag for move (False constructor called)");
	}
}

Move::Move(
	Square given_start,
	Square given_dest,
	ChessColor color,
	MoveFlag flag) :
	_start(given_start),
	_destination(given_dest),
	_flag(flag),
	_color_of_piece(color)
{
	if ((flag == MoveFlag::promote_queen ||
		flag == MoveFlag::promote_rook ||
		flag == MoveFlag::promote_bishop ||
		flag == MoveFlag::promote_knight) == false)
	{
		throw std::invalid_argument("Invalid flag for move (False constructor called)");
	}
}

Move::Move(ChessColor col, CastlingType castle_type) :
	_start(SQUARE_NONE),
	_destination(SQUARE_NONE),
	_flag(castle),
	_color_of_piece(col)
{
	if (_flag != castle)
	{
		throw std::invalid_argument("Invalid flag for move (False constructor called)");
	}

	_start = START_SQUARE_KING_CASTLING[col];
	_destination = DESTINATION_SQUARE_KING_CASTLING[col][castle_type];
}

Square Move::get_start() const
{
	return _start;
}

Square Move::get_destination() const
{
	return _destination;
}

MoveFlag Move::get_flag() const
{
	return _flag;
}

void Move::execute(BoardRepresentation& board) const
{
	//TODO Implement getting castling squares
	//board.copySquareToPos(_start, _destination);
	//board.del_at_pos(_start);
}

std::string Move::get_string() const
{	
	if (_flag == castle)
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