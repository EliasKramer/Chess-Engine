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
			Assert::IsTrue(PAWN_ATTACK_DIRECTION[White][0] == NORTH_EAST);
			Assert::IsTrue(PAWN_ATTACK_DIRECTION[White][1] == NORTH_WEST);
			Assert::IsTrue(PAWN_ATTACK_DIRECTION[Black][0] == SOUTH_EAST);
			Assert::IsTrue(PAWN_ATTACK_DIRECTION[Black][1] == SOUTH_WEST);
		}
		TEST_METHOD(pawnAttackBB)
		{
			Assert::IsTrue(PAWN_ATTACK_BB[White][A1] == 0x200ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[White][B1] == 0x500ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[White][C1] == 0xa00ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[White][D1] == 0x1400ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[White][E1] == 0x2800ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[White][F1] == 0x5000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[White][G1] == 0xa000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[White][H1] == 0x4000ULL);
			
			Assert::IsTrue(PAWN_ATTACK_BB[White][A2] == 0x20000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[White][B2] == 0x50000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[White][C2] == 0xa0000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[White][D2] == 0x140000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[White][E2] == 0x280000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[White][F2] == 0x500000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[White][G2] == 0xa00000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[White][H2] == 0x400000ULL);
			
			Assert::IsTrue(PAWN_ATTACK_BB[Black][A5] == 0x2000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[Black][B5] == 0x5000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[Black][C5] == 0xa000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[Black][D5] == 0x14000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[Black][E5] == 0x28000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[Black][F5] == 0x50000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[Black][G5] == 0xa0000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[Black][H5] == 0x40000000ULL);
			
			Assert::IsTrue(PAWN_ATTACK_BB[Black][A6] == 0x200000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[Black][B6] == 0x500000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[Black][C6] == 0xa00000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[Black][D6] == 0x1400000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[Black][E6] == 0x2800000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[Black][F6] == 0x5000000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[Black][G6] == 0xa000000000ULL);
			Assert::IsTrue(PAWN_ATTACK_BB[Black][H6] == 0x4000000000ULL);
		}
	};
}