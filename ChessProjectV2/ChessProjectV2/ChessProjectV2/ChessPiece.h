#pragma once
#include "DataAndTypes.h"
#include "HelpMethods.h"
class ChessPiece
{
private:
	PieceType _type;
	ChessColor _color;

	friend bool operator ==(
		const ChessPiece& first,
		const ChessPiece& second);

	friend bool operator !=(
		const ChessPiece& first,
		const ChessPiece& second);
public:
	ChessPiece(ChessColor color, PieceType type);
	ChessPiece(char fen_char);
	
	PieceType getType();
	ChessColor getColor();
};
bool operator ==(
	const ChessPiece& first,
	const ChessPiece& second);
bool operator !=(
	const ChessPiece& first,
	const ChessPiece& second);