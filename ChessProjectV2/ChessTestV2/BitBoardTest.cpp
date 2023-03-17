#include "CppUnitTest.h"
#include "../ChessProjectV2/BitBoard.h"
#include "../ChessProjectV2/DataAndTypes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BitBoardTest
{
	TEST_CLASS(BitBoardTest)
	{
	public:

		TEST_METHOD(BitBoardInitialising)
		{
			Assert::AreEqual(0ULL, BITBOARD_NONE);
			Assert::AreEqual(0xffffffffffffffffULL, BITBOARD_ALL);
			
			Assert::AreEqual(0x101010101010101ULL, FILE_A);
			Assert::AreEqual(0x202020202020202ULL, FILE_B);
			Assert::AreEqual(0x404040404040404ULL, FILE_C);
			Assert::AreEqual(0x808080808080808ULL, FILE_D);
			Assert::AreEqual(0x1010101010101010ULL, FILE_E);
			Assert::AreEqual(0x2020202020202020ULL, FILE_F);
			Assert::AreEqual(0x4040404040404040ULL, FILE_G);
			Assert::AreEqual(0x8080808080808080ULL, FILE_H);

			Assert::AreEqual(0xffULL, RANK_1);
			Assert::AreEqual(0xff00ULL, RANK_2);
			Assert::AreEqual(0xff0000ULL, RANK_3);
			Assert::AreEqual(0xff000000ULL, RANK_4);
			Assert::AreEqual(0xff00000000ULL, RANK_5);
			Assert::AreEqual(0xff0000000000ULL, RANK_6);
			Assert::AreEqual(0xff000000000000ULL, RANK_7);
			Assert::AreEqual(0xff00000000000000ULL, RANK_8);

			Assert::AreEqual(0x1ULL, BB_SQUARE[A1]);
			Assert::AreEqual(0x2ULL, BB_SQUARE[B1]);
			Assert::AreEqual(0x4ULL, BB_SQUARE[C1]);
			Assert::AreEqual(0x8ULL, BB_SQUARE[D1]);
			Assert::AreEqual(0x10ULL, BB_SQUARE[E1]);
			Assert::AreEqual(0x20ULL, BB_SQUARE[F1]);
			Assert::AreEqual(0x40ULL, BB_SQUARE[G1]);
			Assert::AreEqual(0x80ULL, BB_SQUARE[H1]);

			Assert::AreEqual(0x100ULL, BB_SQUARE[A2]);
			Assert::AreEqual(0x200ULL, BB_SQUARE[B2]);
			Assert::AreEqual(0x400ULL, BB_SQUARE[C2]);
			Assert::AreEqual(0x800ULL, BB_SQUARE[D2]);
			Assert::AreEqual(0x1000ULL, BB_SQUARE[E2]);
			Assert::AreEqual(0x2000ULL, BB_SQUARE[F2]);
			Assert::AreEqual(0x4000ULL, BB_SQUARE[G2]);
			Assert::AreEqual(0x8000ULL, BB_SQUARE[H2]);
			
			Assert::AreEqual(0x10000ULL, BB_SQUARE[A3]);
			Assert::AreEqual(0x20000ULL, BB_SQUARE[B3]);
			Assert::AreEqual(0x40000ULL, BB_SQUARE[C3]);
			Assert::AreEqual(0x80000ULL, BB_SQUARE[D3]);
			Assert::AreEqual(0x100000ULL, BB_SQUARE[E3]);
			Assert::AreEqual(0x200000ULL, BB_SQUARE[F3]);
			Assert::AreEqual(0x400000ULL, BB_SQUARE[G3]);
			Assert::AreEqual(0x800000ULL, BB_SQUARE[H3]);
			
			Assert::AreEqual(0x1000000ULL, BB_SQUARE[A4]);
			Assert::AreEqual(0x2000000ULL, BB_SQUARE[B4]);
			Assert::AreEqual(0x4000000ULL, BB_SQUARE[C4]);
			Assert::AreEqual(0x8000000ULL, BB_SQUARE[D4]);
			Assert::AreEqual(0x10000000ULL, BB_SQUARE[E4]);
			Assert::AreEqual(0x20000000ULL, BB_SQUARE[F4]);
			Assert::AreEqual(0x40000000ULL, BB_SQUARE[G4]);
			Assert::AreEqual(0x80000000ULL, BB_SQUARE[H4]);
			
			Assert::AreEqual(0x100000000ULL, BB_SQUARE[A5]);
			Assert::AreEqual(0x200000000ULL, BB_SQUARE[B5]);
			Assert::AreEqual(0x400000000ULL, BB_SQUARE[C5]);
			Assert::AreEqual(0x800000000ULL, BB_SQUARE[D5]);
			Assert::AreEqual(0x1000000000ULL, BB_SQUARE[E5]);
			Assert::AreEqual(0x2000000000ULL, BB_SQUARE[F5]);
			Assert::AreEqual(0x4000000000ULL, BB_SQUARE[G5]);
			Assert::AreEqual(0x8000000000ULL, BB_SQUARE[H5]);
			
			Assert::AreEqual(0x10000000000ULL, BB_SQUARE[A6]);
			Assert::AreEqual(0x20000000000ULL, BB_SQUARE[B6]);
			Assert::AreEqual(0x40000000000ULL, BB_SQUARE[C6]);
			Assert::AreEqual(0x80000000000ULL, BB_SQUARE[D6]);
			Assert::AreEqual(0x100000000000ULL, BB_SQUARE[E6]);
			Assert::AreEqual(0x200000000000ULL, BB_SQUARE[F6]);
			Assert::AreEqual(0x400000000000ULL, BB_SQUARE[G6]);
			Assert::AreEqual(0x800000000000ULL, BB_SQUARE[H6]);
			
			Assert::AreEqual(0x1000000000000ULL, BB_SQUARE[A7]);
			Assert::AreEqual(0x2000000000000ULL, BB_SQUARE[B7]);
			Assert::AreEqual(0x4000000000000ULL, BB_SQUARE[C7]);
			Assert::AreEqual(0x8000000000000ULL, BB_SQUARE[D7]);
			Assert::AreEqual(0x10000000000000ULL, BB_SQUARE[E7]);
			Assert::AreEqual(0x20000000000000ULL, BB_SQUARE[F7]);
			Assert::AreEqual(0x40000000000000ULL, BB_SQUARE[G7]);
			Assert::AreEqual(0x80000000000000ULL, BB_SQUARE[H7]);
	
			Assert::AreEqual(0x100000000000000ULL, BB_SQUARE[A8]);
			Assert::AreEqual(0x200000000000000ULL, BB_SQUARE[B8]);
			Assert::AreEqual(0x400000000000000ULL, BB_SQUARE[C8]);
			Assert::AreEqual(0x800000000000000ULL, BB_SQUARE[D8]);
			Assert::AreEqual(0x1000000000000000ULL, BB_SQUARE[E8]);
			Assert::AreEqual(0x2000000000000000ULL, BB_SQUARE[F8]);
			Assert::AreEqual(0x4000000000000000ULL, BB_SQUARE[G8]);
			Assert::AreEqual(0x8000000000000000ULL, BB_SQUARE[H8]);

			//some tests to not get a false positive
			Assert::AreNotEqual(0x1ULL, BB_SQUARE[B2]);
			Assert::AreNotEqual(0x80000000000000ULL, BB_SQUARE[H8]);
		}
		TEST_METHOD(SquaresAreTheSameAsOverlappingFilesAndRanks)
		{
			Assert::AreEqual(BB_SQUARE[A1], FILE_A & RANK_1);
			Assert::AreEqual(BB_SQUARE[B1], FILE_B & RANK_1);
			Assert::AreEqual(BB_SQUARE[C1], FILE_C & RANK_1);
			Assert::AreEqual(BB_SQUARE[D1], FILE_D & RANK_1);
			Assert::AreEqual(BB_SQUARE[E1], FILE_E & RANK_1);
			Assert::AreEqual(BB_SQUARE[F1], FILE_F & RANK_1);
			Assert::AreEqual(BB_SQUARE[G1], FILE_G & RANK_1);
			Assert::AreEqual(BB_SQUARE[H1], FILE_H & RANK_1);

			Assert::AreEqual(BB_SQUARE[A2], FILE_A & RANK_2);
			Assert::AreEqual(BB_SQUARE[B2], FILE_B & RANK_2);
			Assert::AreEqual(BB_SQUARE[C2], FILE_C & RANK_2);
			Assert::AreEqual(BB_SQUARE[D2], FILE_D & RANK_2);
			Assert::AreEqual(BB_SQUARE[E2], FILE_E & RANK_2);
			Assert::AreEqual(BB_SQUARE[F2], FILE_F & RANK_2);
			Assert::AreEqual(BB_SQUARE[G2], FILE_G & RANK_2);
			Assert::AreEqual(BB_SQUARE[H2], FILE_H & RANK_2);
			
			Assert::AreEqual(BB_SQUARE[A3], FILE_A & RANK_3);
			Assert::AreEqual(BB_SQUARE[B3], FILE_B & RANK_3);
			Assert::AreEqual(BB_SQUARE[C3], FILE_C & RANK_3);
			Assert::AreEqual(BB_SQUARE[D3], FILE_D & RANK_3);
			Assert::AreEqual(BB_SQUARE[E3], FILE_E & RANK_3);
			Assert::AreEqual(BB_SQUARE[F3], FILE_F & RANK_3);
			Assert::AreEqual(BB_SQUARE[G3], FILE_G & RANK_3);
			Assert::AreEqual(BB_SQUARE[H3], FILE_H & RANK_3);

			Assert::AreEqual(BB_SQUARE[A4], FILE_A & RANK_4);
			Assert::AreEqual(BB_SQUARE[B4], FILE_B & RANK_4);
			Assert::AreEqual(BB_SQUARE[C4], FILE_C & RANK_4);
			Assert::AreEqual(BB_SQUARE[D4], FILE_D & RANK_4);
			Assert::AreEqual(BB_SQUARE[E4], FILE_E & RANK_4);
			Assert::AreEqual(BB_SQUARE[F4], FILE_F & RANK_4);
			Assert::AreEqual(BB_SQUARE[G4], FILE_G & RANK_4);
			Assert::AreEqual(BB_SQUARE[H4], FILE_H & RANK_4);
			
			Assert::AreEqual(BB_SQUARE[A5], FILE_A & RANK_5);
			Assert::AreEqual(BB_SQUARE[B5], FILE_B & RANK_5);
			Assert::AreEqual(BB_SQUARE[C5], FILE_C & RANK_5);
			Assert::AreEqual(BB_SQUARE[D5], FILE_D & RANK_5);
			Assert::AreEqual(BB_SQUARE[E5], FILE_E & RANK_5);
			Assert::AreEqual(BB_SQUARE[F5], FILE_F & RANK_5);
			Assert::AreEqual(BB_SQUARE[G5], FILE_G & RANK_5);
			Assert::AreEqual(BB_SQUARE[H5], FILE_H & RANK_5);
			
			Assert::AreEqual(BB_SQUARE[A6], FILE_A & RANK_6);
			Assert::AreEqual(BB_SQUARE[B6], FILE_B & RANK_6);
			Assert::AreEqual(BB_SQUARE[C6], FILE_C & RANK_6);
			Assert::AreEqual(BB_SQUARE[D6], FILE_D & RANK_6);
			Assert::AreEqual(BB_SQUARE[E6], FILE_E & RANK_6);
			Assert::AreEqual(BB_SQUARE[F6], FILE_F & RANK_6);
			Assert::AreEqual(BB_SQUARE[G6], FILE_G & RANK_6);
			Assert::AreEqual(BB_SQUARE[H6], FILE_H & RANK_6);
			
			Assert::AreEqual(BB_SQUARE[A7], FILE_A & RANK_7);
			Assert::AreEqual(BB_SQUARE[B7], FILE_B & RANK_7);
			Assert::AreEqual(BB_SQUARE[C7], FILE_C & RANK_7);
			Assert::AreEqual(BB_SQUARE[D7], FILE_D & RANK_7);
			Assert::AreEqual(BB_SQUARE[E7], FILE_E & RANK_7);
			Assert::AreEqual(BB_SQUARE[F7], FILE_F & RANK_7);
			Assert::AreEqual(BB_SQUARE[G7], FILE_G & RANK_7);
			Assert::AreEqual(BB_SQUARE[H7], FILE_H & RANK_7);
				
			Assert::AreEqual(BB_SQUARE[A8], FILE_A & RANK_8);
			Assert::AreEqual(BB_SQUARE[B8], FILE_B & RANK_8);
			Assert::AreEqual(BB_SQUARE[C8], FILE_C & RANK_8);
			Assert::AreEqual(BB_SQUARE[D8], FILE_D & RANK_8);
			Assert::AreEqual(BB_SQUARE[E8], FILE_E & RANK_8);
			Assert::AreEqual(BB_SQUARE[F8], FILE_F & RANK_8);
			Assert::AreEqual(BB_SQUARE[G8], FILE_G & RANK_8);
			Assert::AreEqual(BB_SQUARE[H8], FILE_H & RANK_8);
		}
		TEST_METHOD(overlappingSquareWithBBTest)
		{
			Assert::IsTrue(squareOverlapsWithBB(A1, FILE_A));
			Assert::IsTrue(squareOverlapsWithBB(A1, RANK_1));
			
			Assert::IsTrue(squareOverlapsWithBB(D3, FILE_D));
			Assert::IsTrue(squareOverlapsWithBB(D3, RANK_3));

			Assert::IsFalse(squareOverlapsWithBB(H8, RANK_7));
			Assert::IsFalse(squareOverlapsWithBB(H8, FILE_G));
		}
	};
}