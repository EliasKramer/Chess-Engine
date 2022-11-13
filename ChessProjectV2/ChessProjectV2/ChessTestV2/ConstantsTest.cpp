#include "CppUnitTest.h"
#include "../ChessProjectV2/Constants.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ConstantsTests
{
	TEST_CLASS(ConstantsTests)
	{
	public:
		TEST_METHOD(testKnightAttacks)
		{
			//dont worry i didn't write these tests manually.
			//copilot rules
			//to see how the result look on a bitboard do so on: https://tearth.dev/bitboard-viewer/

			Assert::AreEqual(KNIGHT_ATTACK_BB[A1], 0x20400ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[B1], 0x50800ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[C1], 0xa1100ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[D1], 0x142200ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[E1], 0x284400ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[F1], 0x508800ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[G1], 0xa01000ULL);

			Assert::AreEqual(KNIGHT_ATTACK_BB[A2], 0x2040004ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[B2], 0x5080008ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[C2], 0xa110011ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[D2], 0x14220022ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[E2], 0x28440044ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[F2], 0x50880088ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[G2], 0xa0100010ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[H2], 0x40200020ULL);

			Assert::AreEqual(KNIGHT_ATTACK_BB[A3], 0x204000402ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[B3], 0x508000805ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[C3], 0xa1100110aULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[D3], 0x1422002214ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[E3], 0x2844004428ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[F3], 0x5088008850ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[G3], 0xa0100010a0ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[H3], 0x4020002040ULL);

			Assert::AreEqual(KNIGHT_ATTACK_BB[A4], 0x20400040200ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[B4], 0x50800080500ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[C4], 0xa1100110a00ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[D4], 0x142200221400ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[E4], 0x284400442800ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[F4], 0x508800885000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[G4], 0xa0100010a000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[H4], 0x402000204000ULL);

			Assert::AreEqual(KNIGHT_ATTACK_BB[A5], 0x2040004020000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[B5], 0x5080008050000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[C5], 0xa1100110a0000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[D5], 0x14220022140000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[E5], 0x28440044280000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[F5], 0x50880088500000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[G5], 0xa0100010a00000ULL);

			Assert::AreEqual(KNIGHT_ATTACK_BB[A6], 0x204000402000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[B6], 0x508000805000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[C6], 0xa1100110a000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[D6], 0x1422002214000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[E6], 0x2844004428000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[F6], 0x5088008850000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[G6], 0xa0100010a0000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[H6], 0x4020002040000000ULL);

			//cannot set numbers that are that high
			/*Assert::AreEqual(KNIGHT_ATTACK_BB[A7], 0x20400040200000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[B7], 0x50800080500000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[C7], 0xa1100110a00000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[D7], 0x142200221400000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[E7], 0x284400442800000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[F7], 0x508800885000000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[G7], 0xa0100010a000000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[H7], 0x402000204000000000ULL);

			Assert::AreEqual(KNIGHT_ATTACK_BB[A8], 0x2040004020000000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[B8], 0x5080008050000000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[C8], 0xa1100110a0000000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[D8], 0x14220022140000000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[E8], 0x28440044280000000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[F8], 0x50880088500000000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[G8], 0xa0100010a00000000000ULL);
			Assert::AreEqual(KNIGHT_ATTACK_BB[H8], 0x40200020400000000000ULL);*/
		}
		TEST_METHOD(pawnAttackDirections)
		{
			Assert::IsTrue(PAWN_ATTACK_DIRECTION[white][0] == NORTH_EAST);
			Assert::IsTrue(PAWN_ATTACK_DIRECTION[white][1] == NORTH_WEST);
			Assert::IsTrue(PAWN_ATTACK_DIRECTION[black][0] == SOUTH_EAST);
			Assert::IsTrue(PAWN_ATTACK_DIRECTION[black][1] == SOUTH_WEST);
		}
		TEST_METHOD(pawnAttackBB)
		{
			Assert::IsTrue(PAWN_ATTACK_BB[white][A1] == 0x200ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[white][B1] == 0x500ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[white][C1] == 0xa00ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[white][D1] == 0x1400ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[white][E1] == 0x2800ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[white][F1] == 0x5000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[white][G1] == 0xa000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[white][H1] == 0x4000ULL);

			Assert::IsTrue(PAWN_ATTACK_BB[white][A2] == 0x20000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[white][B2] == 0x50000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[white][C2] == 0xa0000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[white][D2] == 0x140000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[white][E2] == 0x280000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[white][F2] == 0x500000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[white][G2] == 0xa00000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[white][H2] == 0x400000ULL);

			Assert::IsTrue(PAWN_ATTACK_BB[black][A5] == 0x2000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[black][B5] == 0x5000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[black][C5] == 0xa000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[black][D5] == 0x14000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[black][E5] == 0x28000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[black][F5] == 0x50000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[black][G5] == 0xa0000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[black][H5] == 0x40000000ULL);

			Assert::IsTrue(PAWN_ATTACK_BB[black][A6] == 0x200000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[black][B6] == 0x500000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[black][C6] == 0xa00000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[black][D6] == 0x1400000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[black][E6] == 0x2800000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[black][F6] == 0x5000000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[black][G6] == 0xa000000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[black][H6] == 0x4000000000ULL);
		}
		TEST_METHOD(testKingAttackFieldBB)
		{
			Assert::IsTrue(KING_ATTACKS_BB[A1] == 0x302ULL);
			Assert::IsTrue(KING_ATTACKS_BB[B1] == 0x705ULL);
			Assert::IsTrue(KING_ATTACKS_BB[C1] == 0xe0aULL);
			Assert::IsTrue(KING_ATTACKS_BB[D1] == 0x1c14ULL);
			Assert::IsTrue(KING_ATTACKS_BB[E1] == 0x3828ULL);
			Assert::IsTrue(KING_ATTACKS_BB[F1] == 0x7050ULL);
			Assert::IsTrue(KING_ATTACKS_BB[G1] == 0xe0a0ULL);
			Assert::IsTrue(KING_ATTACKS_BB[H1] == 0xc040ULL);

			Assert::IsTrue(KING_ATTACKS_BB[A2] == 0x30203ULL);
			Assert::IsTrue(KING_ATTACKS_BB[B2] == 0x70507ULL);
			Assert::IsTrue(KING_ATTACKS_BB[C2] == 0xe0a0eULL);
			Assert::IsTrue(KING_ATTACKS_BB[D2] == 0x1c141cULL);
			Assert::IsTrue(KING_ATTACKS_BB[E2] == 0x382838ULL);
			Assert::IsTrue(KING_ATTACKS_BB[F2] == 0x705070ULL);
			Assert::IsTrue(KING_ATTACKS_BB[G2] == 0xe0a0e0ULL);
			Assert::IsTrue(KING_ATTACKS_BB[H2] == 0xc040c0ULL);

			Assert::IsTrue(KING_ATTACKS_BB[A3] == 0x3020300ULL);
			Assert::IsTrue(KING_ATTACKS_BB[B3] == 0x7050700ULL);
			Assert::IsTrue(KING_ATTACKS_BB[C3] == 0xe0a0e00ULL);
			Assert::IsTrue(KING_ATTACKS_BB[D3] == 0x1c141c00ULL);
			Assert::IsTrue(KING_ATTACKS_BB[E3] == 0x38283800ULL);
			Assert::IsTrue(KING_ATTACKS_BB[F3] == 0x70507000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[G3] == 0xe0a0e000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[H3] == 0xc040c000ULL);

			Assert::IsTrue(KING_ATTACKS_BB[A4] == 0x302030000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[B4] == 0x705070000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[C4] == 0xe0a0e0000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[D4] == 0x1c141c0000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[E4] == 0x3828380000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[F4] == 0x7050700000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[G4] == 0xe0a0e00000LL);
			Assert::IsTrue(KING_ATTACKS_BB[H4] == 0xc040c00000ULL);

			Assert::IsTrue(KING_ATTACKS_BB[A5] == 0x30203000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[B5] == 0x70507000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[C5] == 0xe0a0e000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[D5] == 0x1c141c000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[E5] == 0x382838000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[F5] == 0x705070000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[G5] == 0xe0a0e0000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[H5] == 0xc040c0000000ULL);

			Assert::IsTrue(KING_ATTACKS_BB[A6] == 0x3020300000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[B6] == 0x7050700000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[C6] == 0xe0a0e00000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[D6] == 0x1c141c00000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[E6] == 0x38283800000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[F6] == 0x70507000000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[G6] == 0xe0a0e000000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[H6] == 0xc040c000000000ULL);

			Assert::IsTrue(KING_ATTACKS_BB[A7] == 0x302030000000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[B7] == 0x705070000000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[C7] == 0xe0a0e0000000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[D7] == 0x1c141c0000000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[E7] == 0x3828380000000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[F7] == 0x7050700000000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[G7] == 0xe0a0e00000000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[H7] == 0xc040c00000000000ULL);

			//cannot set numbers that are that high
			/*
			Assert::IsTrue(KING_ATTACKS_BB[A8] == 0x30203000000000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[B8] == 0x70507000000000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[C8] == 0xe0a0e000000000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[D8] == 0x1c141c000000000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[E8] == 0x382838000000000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[F8] == 0x705070000000000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[G8] == 0xe0a0e0000000000000ULL);
			Assert::IsTrue(KING_ATTACKS_BB[H8] == 0xc040c0000000000000ULL);*/
		}
		TEST_METHOD(testOrderOfSlidingArray)
		{
			//only change this order if you implement another
			//function for finding what sliding pieces attack a square

			Assert::IsTrue(NORTH == ALL_SLIDING_DIRECTIONS[0]);
			Assert::IsTrue(EAST == ALL_SLIDING_DIRECTIONS[1]);
			Assert::IsTrue(SOUTH == ALL_SLIDING_DIRECTIONS[2]);
			Assert::IsTrue(WEST == ALL_SLIDING_DIRECTIONS[3]);

			Assert::IsTrue(NORTH_EAST == ALL_SLIDING_DIRECTIONS[4]);
			Assert::IsTrue(SOUTH_EAST == ALL_SLIDING_DIRECTIONS[5]);
			Assert::IsTrue(SOUTH_WEST == ALL_SLIDING_DIRECTIONS[6]);
			Assert::IsTrue(NORTH_WEST == ALL_SLIDING_DIRECTIONS[7]);
		}
		TEST_METHOD(backrankTest)
		{
			Assert::AreEqual(RANK_1, BACK_RANK[white]);
			Assert::AreEqual(RANK_8, BACK_RANK[black]);
		}
		TEST_METHOD(pieceTypeCharTest)
		{
			Assert::AreEqual('P', PIECETYPE_CHAR[pawn]);
			Assert::AreEqual('N', PIECETYPE_CHAR[knight]);
			Assert::AreEqual('B', PIECETYPE_CHAR[bishop]);
			Assert::AreEqual('R', PIECETYPE_CHAR[rook]);
			Assert::AreEqual('Q', PIECETYPE_CHAR[queen]);
			Assert::AreEqual('K', PIECETYPE_CHAR[king]);
		}
		TEST_METHOD(positionAdditionValueForPieces)
		{
			//TODO - NEEDS TO BE TESTED MORE
			Assert::AreEqual(0, POSITION_VALUE[white][pawn][A1]);
			Assert::AreEqual(5, POSITION_VALUE[white][pawn][A2]);
			Assert::AreEqual(5, POSITION_VALUE[white][pawn][A3]);
			Assert::AreEqual(0, POSITION_VALUE[white][pawn][A4]);
			Assert::AreEqual(5, POSITION_VALUE[white][pawn][A5]);
			Assert::AreEqual(10, POSITION_VALUE[white][pawn][A6]);
			Assert::AreEqual(50, POSITION_VALUE[white][pawn][A7]);
			Assert::AreEqual(0, POSITION_VALUE[white][pawn][A8]);
			
			Assert::AreEqual(0, POSITION_VALUE[black][pawn][E8]);
			Assert::AreEqual(-20, POSITION_VALUE[black][pawn][E7]);
			Assert::AreEqual(0, POSITION_VALUE[black][pawn][E6]);
			Assert::AreEqual(20, POSITION_VALUE[black][pawn][E5]);
			Assert::AreEqual(25, POSITION_VALUE[black][pawn][E4]);
			Assert::AreEqual(30, POSITION_VALUE[black][pawn][E3]);
			Assert::AreEqual(50, POSITION_VALUE[black][pawn][E2]);
			Assert::AreEqual(0, POSITION_VALUE[black][pawn][E1]);
		}
		TEST_METHOD(evaluateGameState)
		{
			Assert::AreEqual(WHITE_WIN_EVAL_VALUE, GAME_STATE_EVALUATION[white_won]);
			Assert::AreEqual(BLACK_WIN_EVAL_VALUE, GAME_STATE_EVALUATION[black_won]);
			Assert::AreEqual(0, GAME_STATE_EVALUATION[stalemate]);
			Assert::AreEqual(0, GAME_STATE_EVALUATION[draw]);
			Assert::AreEqual(-1, GAME_STATE_EVALUATION[ongoing]);
		}
	};
}