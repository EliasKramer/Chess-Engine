#pragma once
#include <string>
const int DIFFERENT_CHESS_COLORS = 2;

enum ChessColor : uint8_t {
	White,
	Black,
	NoColor
};

const int NUMBER_OF_DIFFERENT_PIECE_TYPES = 6;

enum PieceType : uint8_t {
	Pawn,
	Knight,
	Bishop,
	Rook,
	Queen,
	King,
	NoType
};

const int DIFFERENT_CASTLING_TYPES = 2;

enum CastlingType : uint8_t {
	CastleShort,
	CastleLong
};

enum GameState : uint8_t {
	WhiteWon,
	BlackWon,
	Stalemate,
	Draw,
	Ongoing
};

enum MoveFlag : uint8_t {
	Normal,
	Castle,
	EnPassant,
	PromoteQueen,
	PromoteRook,
	PromoteKnight,
	PromoteBishop
};