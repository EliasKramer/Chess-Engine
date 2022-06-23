#pragma once
#include "MetaData.h"
class ChessPiece
{
private:
	PieceType type;
	ChessColor color;
	bool exists;
public:
	ChessPiece(PieceType givenType, ChessColor givenColor);
	ChessPiece();
	bool doesExist();
	PieceType* getType();
	ChessColor* getColor();
};

