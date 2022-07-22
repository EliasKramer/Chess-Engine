#pragma once
#include <string>
enum ChessColor
{
	White,
	Black,
	NoColor
};
enum PieceType
{
	King,
	Queen,
	Rook,
	Bishop,
	Knight,
	Pawn,
	NoType
};
enum CastleType
{
	Short,
	Long
};

const int BOARD_SIZE = 8;

std::string getLongNameOfChessType(PieceType* type);
std::string getShortNameOfChessType(PieceType* type);

std::string getLongNameOfChessColor(ChessColor* color);
std::string getShortNameOfChessColor(ChessColor* color);

unsigned short getValueOfType(PieceType* type);