#pragma once
#include <cstdint>
#include <array>

typedef uint64_t BitBoard;

const BitBoard BITBOARD_ALL = 0xFFFFFFFFFFFFFFFF;
const BitBoard BITBOARD_NONE = 0;

const BitBoard FILE_A = 0x101010101010101ULL;
const BitBoard FILE_B = FILE_A << 1;
const BitBoard FILE_C = FILE_A << 2;
const BitBoard FILE_D = FILE_A << 3;
const BitBoard FILE_E = FILE_A << 4;
const BitBoard FILE_F = FILE_A << 5;
const BitBoard FILE_G = FILE_A << 6;
const BitBoard FILE_H = FILE_A << 7;

const BitBoard RANK_1 = 0xFF;
const BitBoard RANK_2 = RANK_1 << (8 * 1);
const BitBoard RANK_3 = RANK_1 << (8 * 2);
const BitBoard RANK_4 = RANK_1 << (8 * 3);
const BitBoard RANK_5 = RANK_1 << (8 * 4);
const BitBoard RANK_6 = RANK_1 << (8 * 5);
const BitBoard RANK_7 = RANK_1 << (8 * 6);
const BitBoard RANK_8 = RANK_1 << (8 * 7);

enum Square: uint8_t{
	A1, B1, C1, D1, E1, F1, G1, H1,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A8, B8, C8, D8, E8, F8, G8, H8,

	SQUARE_NONE
};

const std::array<BitBoard, 64> BB_SQUARE = []()->std::array<BitBoard, 64> {
	std::array<BitBoard, 64> retVal = {};
	
	for (int i = A1; i <= H8; i++)
	{
		retVal[i] = 1ULL << i;
	}

	return retVal;
}();