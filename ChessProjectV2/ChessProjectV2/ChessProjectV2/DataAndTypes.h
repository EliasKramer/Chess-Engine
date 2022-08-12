#pragma once
#include <string>
#include "HelpMethods.h"
const int DIFFERENT_CHESS_COLORS = 2;

enum ChessColor {
	White,
	Black
};

const int NUMBER_OF_DIFFERENT_PIECE_TYPES = 6;

enum PieceType {
	Pawn,
	Rook,
	Knight,
	Bishop,
	Queen,
	King
};

const int DIFFERENT_CASTLING_TYPES = 2;

enum CastlingType {
	CastleShort,
	CastleLong
};

ChessColor getColorOfFenChar(
	char c,
	std::string errorMsgPrefix = "ERROR");

CastlingType getCastlingTypeOfFenChar(
	char c,
	std::string errorMsgPrefix = "ERROR");

