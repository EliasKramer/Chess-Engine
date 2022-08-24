#pragma once
#include <string>
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
