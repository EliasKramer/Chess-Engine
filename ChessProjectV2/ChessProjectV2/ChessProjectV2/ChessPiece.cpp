#include "ChessPiece.h"

ChessPiece::ChessPiece(
	ChessColor color,
	PieceType type) :
	_color(color),
	_type(type)
{}

ChessPiece::ChessPiece(char fen_char)
{
	if (fen_char >= 'a' && fen_char <= 'z')
	{
		_color = Black;
	}
	else if (fen_char >= 'A' && fen_char <= 'Z')
	{
		_color = White;
		//makes a upper case char to a lower case.
		//(for easier comparison later when trying to find type)
		fen_char += ('a' - 'A');
	}
	else
	{
		throw "ERROR Tried to create Chess Piece from an invalid fen character. (Color not found)";
	}

	switch (fen_char)
	{
	case 'p':
		_type = Pawn;
		break;
	case 'r':
		_type = Rook;
		break;
	case 'n':
		_type = Knight;
		break;
	case 'b':
		_type = Bishop;
		break;
	case 'q':
		_type = Queen;
		break;
	case 'k':
		_type = King;
		break;
	default:
		throw "ERROR Tried to create Chess Piece from an invalid fen character. (Type not found)";
	}
}

PieceType ChessPiece::getType()
{
	return _type;
}

ChessColor ChessPiece::getColor()
{
	return _color;
}