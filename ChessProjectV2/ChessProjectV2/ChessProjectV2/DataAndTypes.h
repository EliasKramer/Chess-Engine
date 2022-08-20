#pragma once
#include <string>
#include "HelpMethods.h"
#include "BitBoard.h"
const int DIFFERENT_CHESS_COLORS = 2;

enum ChessColor : uint8_t {
	White,
	Black
};

const int NUMBER_OF_DIFFERENT_PIECE_TYPES = 6;

enum PieceType : uint8_t {
	Pawn,
	Rook,
	Knight,
	Bishop,
	Queen,
	King
};

const int DIFFERENT_CASTLING_TYPES = 2;

enum CastlingType : uint8_t {
	CastleShort,
	CastleLong
};

ChessColor getColorOfFenChar(
	char c,
	std::string errorMsgPrefix = "ERROR");

CastlingType getCastlingTypeOfFenChar(
	char c,
	std::string errorMsgPrefix = "ERROR");

Square getSquareFromString(
	std::string str,
	std::string errorMsgPrefix = "ERROR");