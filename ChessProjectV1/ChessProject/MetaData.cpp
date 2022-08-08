#include "MetaData.h"
std::string getLongNameOfChessType(PieceType* type)
{
	switch (*type)
	{
	case PieceType::King:
		return "King";
	case PieceType::Queen:
		return "Queen";
	case PieceType::Rook:
		return "Rook";
	case PieceType::Bishop:
		return "Bishop";
	case PieceType::Knight:
		return "Knight";
	case PieceType::Pawn:
		return "Pawn";
	default:
		return "NoType";
	}
}

std::string getShortNameOfChessType(PieceType* type)
{
	switch (*type)
	{
	case PieceType::King:
		return "K";
	case PieceType::Queen:
		return "Q";
	case PieceType::Rook:
		return "R";
	case PieceType::Bishop:
		return "B";
	case PieceType::Knight:
		return "N";
	case PieceType::Pawn:
		return "P";
	default:
		return " ";
	}
}
std::string getLongNameOfChessColor(ChessColor* color)
{
	switch (*color)
	{
	case ChessColor::White:
		return "White";
	case ChessColor::Black:
		return "Black";
	default:
		return "NoColor";
	}
}
std::string getShortNameOfChessColor(ChessColor* color)
{
	switch (*color)
	{
	case ChessColor::White:
		return "W";
	case ChessColor::Black:
		return "B";
	default:
		return " ";
	}
}

ChessColor getOppositeColor(ChessColor color)
{
	if (color == ChessColor::NoColor)
	{
		return ChessColor::NoColor;
	}
	else {
		return color == ChessColor::White ? 
			ChessColor::Black : 
			ChessColor::White;
	}
}

unsigned short getValueOfType(PieceType* type)
{
	switch (*type)
	{
	case PieceType::King:
		return USHRT_MAX;
	case PieceType::Queen:
		return 9;
	case PieceType::Rook:
		return 5;
	case PieceType::Bishop:
		return 3;
	case PieceType::Knight:
		return 3;
	case PieceType::Pawn:
		return 1;
	default:
		return -1;
		break;
	}
}
