#pragma once
#include "DataAndTypes.h"
class ChessPiece
{
private:
	PieceType _type;
	ChessColor _color;
public:
	ChessPiece(ChessColor color, PieceType type);
	ChessPiece(char fen_char);
	
	PieceType getType();
	ChessColor getColor();
};