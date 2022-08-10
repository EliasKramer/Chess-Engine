#pragma once
#include "ChessPiece.h"
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