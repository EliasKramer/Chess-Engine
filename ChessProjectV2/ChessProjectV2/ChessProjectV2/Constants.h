#pragma once
#include "BitBoard.h"
#include "DataAndTypes.h"
#include <vector>
#include <map>

const Direction KNIGHT_DIRECTIONS[8] = {
	NORTH_NORTH_EAST,
	EAST_NORTH_EAST,
	EAST_SOUTH_EAST,
	SOUTH_SOUTH_EAST,
	SOUTH_SOUTH_WEST,
	WEST_SOUTH_WEST,
	WEST_NORTH_WEST,
	NORTH_NORTH_WEST
};

const Direction ALL_SLIDING_DIRECTIONS[8] = {
	NORTH,
	EAST,
	SOUTH,
	WEST,
	NORTH_EAST,
	SOUTH_EAST,
	SOUTH_WEST,
	NORTH_WEST
};

const Direction ROOK_DIRECTIONS[4] = {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

const Direction BISHOP_DIRECTIONS[4] = {
	NORTH_EAST,
	SOUTH_EAST,
	SOUTH_WEST,
	NORTH_WEST
};

const Direction PAWN_ATTACK_DIRECTION[2][2]{
	{NORTH_EAST, NORTH_WEST},
	{SOUTH_EAST, SOUTH_WEST}
};

const BitBoard BACK_RANK[2] = { RANK_1, RANK_8 };

//first dimension is color, second is castling type and 
//third is the list of squares, that have to be not attacked when castling
const std::array<std::array<std::array<Square, 3>, 2>, 2> SQUARES_FOR_KING_CASTLING =
[]()->std::array<std::array<std::array<Square, 3>, 2>, 2> {

	std::array<std::array<std::array<Square, 3>, 2>, 2> result = {};

	result[White][CastleShort][0] = E1;
	result[White][CastleShort][1] = F1;
	result[White][CastleShort][2] = G1;

	result[White][CastleLong][0] = E1;
	result[White][CastleLong][1] = D1;
	result[White][CastleLong][2] = C1;

	result[Black][CastleShort][0] = E8;
	result[Black][CastleShort][1] = F8;
	result[Black][CastleShort][2] = G8;

	result[Black][CastleLong][0] = E8;
	result[Black][CastleLong][1] = D8;
	result[Black][CastleLong][2] = C8;

	return result;
}();

//the first dimension is color, second is castling type
//third on the first idx is start and second idx is destination
const std::array<std::array<std::array<Square, 2>, 2>, 2> SQUARES_FOR_ROOK_CASTLING =
[]()->std::array<std::array<std::array<Square, 2>, 2>, 2> {
	std::array<std::array<std::array<Square, 2>, 2>, 2> result = {};

	result[White][CastleShort][0] = H1;
	result[White][CastleShort][1] = F1;

	result[White][CastleLong][0] = A1;
	result[White][CastleLong][1] = D1;

	result[Black][CastleShort][0] = H8;
	result[Black][CastleShort][1] = F8;

	result[Black][CastleLong][0] = A8;
	result[Black][CastleLong][1] = D8;

	return result;
}();

const std::array<BitBoard, 64> KNIGHT_ATTACK_BB = []()->std::array<BitBoard, 64> {
	std::array<BitBoard, 64> result = {};

	for (int i = A1; i <= H8; i++)
	{
		BitBoard currBitBoard = BITBOARD_NONE;

		Square currSquare = (Square)i;
		for (int j = 0; j < 8; j++)
		{
			Direction dir = KNIGHT_DIRECTIONS[j];
			if (destinationIsOnBoard(currSquare, dir))
			{
				currBitBoard |= BB_SQUARE[i + dir];
			}
		}

		result[i] = currBitBoard;
	}

	return result;
}();

const std::array<std::array<BitBoard, 64>, 2> PAWN_ATTACK_BB =
[]()->std::array<std::array<BitBoard, 64>, 2> {

	std::array<std::array<BitBoard, 64>, 2> result = {};

	for (int colorIdx = White; colorIdx <= Black; colorIdx++)
	{
		for (int i = A1; i <= H8; i++)
		{
			Square currSquare = (Square)i;
			for (int j = 0; j < 2; j++)
			{
				Direction dir = PAWN_ATTACK_DIRECTION[colorIdx][j];
				if (destinationIsOnBoard(currSquare, dir))
				{
					result[colorIdx][i] |= BB_SQUARE[i + dir];
				}
			}
		}
	}

	return result;
}();

const std::array<BitBoard, 64> KING_ATTACKS_BB = []()->std::array<BitBoard, 64> {
	std::array<BitBoard, 64> result = {};

	for (int i = A1; i <= H8; i++)
	{
		BitBoard currBitBoard = BITBOARD_NONE;

		Square currSquare = (Square)i;
		for (int j = 0; j < 8; j++)
		{
			Direction dir = ALL_SLIDING_DIRECTIONS[j];
			if (destinationIsOnBoard(currSquare, dir))
			{
				currBitBoard |= BB_SQUARE[i + dir];
			}
		}
		result[i] = currBitBoard;
	}
	return result;
}();

const std::array<std::string, 64> SQUARE_STRING = []()->std::array<std::string, 64> {
	std::array<std::string, 64> result = {};

	for (int i = A1; i <= H8; i++)
	{
		Square currSquare = (Square)i;
		char file = 'a' + (i % 8);
		char rank = '1' + (i / 8);
		result[i] = file;
		result[i] += rank;
	}

	return result;
}();

const BitBoard BACKRANK[2] = { RANK_1, RANK_8 };
const BitBoard CASTLINGSIDE[2] = { FILE_H, FILE_A };
const BitBoard KINGFILE = FILE_E;
const BitBoard SQUARES_EFFECTED_BY_CASTLING_BB =
BB_SQUARE[A1] | BB_SQUARE[E1] | BB_SQUARE[H1] |
BB_SQUARE[A8] | BB_SQUARE[E8] | BB_SQUARE[H8];

const char PIECETYPE_CHAR[NUMBER_OF_DIFFERENT_PIECE_TYPES] = {'P', 'N', 'B', 'R', 'Q', 'K'};

const std::string COLOR_STRING[2] = { "White", "Black" };

const std::map<PieceType, int> PIECETYPE_VALUE = {
	{Pawn, 100},
	{Knight, 300},
	{Bishop, 300},
	{Rook, 500},
	{Queen, 900},
};