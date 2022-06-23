#include "ChessPiece.h"

ChessPiece::ChessPiece(PieceType givenType, ChessColor givenColor)
{
	exists = givenType != PieceType::NoType && givenColor != ChessColor::NoColor;
	type = givenType;
	color = givenColor;
}
ChessPiece::ChessPiece() : ChessPiece(PieceType::NoType, ChessColor::NoColor)
{}
bool ChessPiece::doesExist()
{
	return exists;
}
PieceType* ChessPiece::getType()
{
	return &type;
}
ChessColor* ChessPiece::getColor()
{
	return &color;
}