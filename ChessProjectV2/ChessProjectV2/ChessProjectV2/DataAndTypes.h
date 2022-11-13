#pragma once
#include <string>
const int DIFFERENT_CHESS_COLORS = 2;

enum ChessColor : uint8_t {
	white,
	black,
	no_color
};

const int NUMBER_OF_DIFFERENT_PIECE_TYPES = 6;

enum PieceType : uint8_t {
	pawn = 0,
	knight = 1,
	bishop = 2,
	rook = 3,
	queen = 4,
	king = 5,
	no_type = 6
};

const int DIFFERENT_CASTLING_TYPES = 2;

enum CastlingType : uint8_t {
	castle_short = 0,
	castle_long = 1
};

enum GameState : uint8_t {
	white_won = 0,
	black_won = 1,
	stalemate = 2,
	draw = 3,
	ongoing = 4
};

enum MoveFlag : uint8_t {
	normal = 0,
	castle = 1,
	en_passant = 2,
	promote_queen = 3,
	promote_rook = 4,
	promote_knight = 5,
	promote_bishop = 6
};