#include "ChessPiece.h"

ChessPiece::ChessPiece(PieceType givenType, ChessColor givenColor)
{
	exists = givenType != PieceType::NoType && givenColor != ChessColor::NoColor;
	type = givenType;
	color = givenColor;
}
ChessPiece::ChessPiece() : ChessPiece(PieceType::NoType, ChessColor::NoColor)
{}
bool ChessPiece::isValid()
{
	return exists;
}
PieceType* ChessPiece::getType()
{
	return &type;
}
int ChessPiece::getTypeVal() const
{
	return (int)type;
}
ChessColor* ChessPiece::getColor()
{
	return &color;
}

bool ChessPiece::operator ==(const ChessPiece& other) const
{
	return (int)other.type == (int)type &&
		(int)other.color == (int)color;
}
