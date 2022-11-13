#include "ChessPiece.h"

ChessPiece::ChessPiece(
	ChessColor color,
	PieceType type) :
	_color(color),
	_type(type)
{}

ChessPiece::ChessPiece(char fenChar)
{
	_color = get_color_of_fen_char(
		fenChar,
		"ERROR Chess Piece could not be created.");

	
	if (is_upper_case(fenChar))
	{
		fenChar = tolower(fenChar);
	}

	//TODO CHANGE THIS TO ARRAY 
	switch (fenChar)
	{
	case 'p':
		_type = pawn;
		break;
	case 'r':
		_type = rook;
		break;
	case 'n':
		_type = knight;
		break;
	case 'b':
		_type = bishop;
		break;
	case 'q':
		_type = queen;
		break;
	case 'k':
		_type = king;
		break;
	default:
		throw "ERROR Tried to create Chess Piece from an invalid fen character. (Type not found)";
	}
}

PieceType ChessPiece::get_type() const
{
	return _type;
}

ChessColor ChessPiece::get_color() const
{
	return _color;
}

bool ChessPiece::is_valid() const
{
	return _type != no_type && _color != no_color;
}

bool operator==(const ChessPiece& first, const ChessPiece& second)
{
	return 
		first._type == second._type &&
		first._color == second._color;
}

bool operator!=(const ChessPiece& first, const ChessPiece& second)
{
	return !(first == second);
}