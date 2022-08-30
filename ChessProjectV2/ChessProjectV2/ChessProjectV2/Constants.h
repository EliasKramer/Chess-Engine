#pragma once
#include "BitBoard.h"
#include "DataAndTypes.h"
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

const std::array<std::array<BitBoard, 64>,2> PAWN_ATTACK_BB = 
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
