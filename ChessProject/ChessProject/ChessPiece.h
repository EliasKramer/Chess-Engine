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
	bool isValid();
	PieceType* getType();
	int getTypeVal()const;
	ChessColor* getColor();
	bool operator ==(const ChessPiece& other) const;
};