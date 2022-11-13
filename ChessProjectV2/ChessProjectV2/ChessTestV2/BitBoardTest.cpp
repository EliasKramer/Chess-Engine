#include "CppUnitTest.h"
#include "../ChessProjectV2/BitBoard.h"
#include "../ChessProjectV2/DataAndTypes.h"
#include "TestMethods.h"
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
			Assert::IsTrue(square_overlaps_with_BB(A1, FILE_A));
			Assert::IsTrue(square_overlaps_with_BB(A1, RANK_1));
			
			Assert::IsTrue(square_overlaps_with_BB(D3, FILE_D));
			Assert::IsTrue(square_overlaps_with_BB(D3, RANK_3));

			Assert::IsFalse(square_overlaps_with_BB(H8, RANK_7));
			Assert::IsFalse(square_overlaps_with_BB(H8, FILE_G));
		}
		TEST_METHOD(SquaresAreOnTheSameFile)
		{
			Assert::IsTrue(squares_are_same_file(A1, A2));
			Assert::IsTrue(squares_are_same_file(A1, A3));
			Assert::IsTrue(squares_are_same_file(A1, A4));
			Assert::IsTrue(squares_are_same_file(A1, A5));
			Assert::IsTrue(squares_are_same_file(A1, A6));
			Assert::IsTrue(squares_are_same_file(A1, A7));
			Assert::IsTrue(squares_are_same_file(A1, A8));

			Assert::IsTrue(squares_are_same_file(B1, B2));
			Assert::IsTrue(squares_are_same_file(B1, B3));
			Assert::IsTrue(squares_are_same_file(B1, B4));
			Assert::IsTrue(squares_are_same_file(B1, B5));
			Assert::IsTrue(squares_are_same_file(B1, B6));
			Assert::IsTrue(squares_are_same_file(B1, B7));
			Assert::IsTrue(squares_are_same_file(B1, B8));

			Assert::IsTrue(squares_are_same_file(C1, C2));
			Assert::IsTrue(squares_are_same_file(C1, C3));
			Assert::IsTrue(squares_are_same_file(C1, C4));
			Assert::IsTrue(squares_are_same_file(C1, C5));
			Assert::IsTrue(squares_are_same_file(C1, C6));
			Assert::IsTrue(squares_are_same_file(C1, C7));
			Assert::IsTrue(squares_are_same_file(C1, C8));

			Assert::IsTrue(squares_are_same_file(D1, D2));
			Assert::IsTrue(squares_are_same_file(D1, D3));
			Assert::IsTrue(squares_are_same_file(D1, D4));
			Assert::IsTrue(squares_are_same_file(D1, D5));
			Assert::IsTrue(squares_are_same_file(D1, D6));
			Assert::IsTrue(squares_are_same_file(D1, D7));
			Assert::IsTrue(squares_are_same_file(D1, D8));

			Assert::IsTrue(squares_are_same_file(E1, E2));
			Assert::IsTrue(squares_are_same_file(E1, E3));
			Assert::IsTrue(squares_are_same_file(E1, E4));
			Assert::IsTrue(squares_are_same_file(E1, E5));
			Assert::IsTrue(squares_are_same_file(E1, E6));
			Assert::IsTrue(squares_are_same_file(E1, E7));
			Assert::IsTrue(squares_are_same_file(E1, E8));

			Assert::IsTrue(squares_are_same_file(F1, F2));
			Assert::IsTrue(squares_are_same_file(F1, F3));
			Assert::IsTrue(squares_are_same_file(F1, F4));
			Assert::IsTrue(squares_are_same_file(F1, F5));
			Assert::IsTrue(squares_are_same_file(F1, F6));
			Assert::IsTrue(squares_are_same_file(F1, F7));
			Assert::IsTrue(squares_are_same_file(F1, F8));

			Assert::IsTrue(squares_are_same_file(G1, G2));
			Assert::IsTrue(squares_are_same_file(G1, G3));
			Assert::IsTrue(squares_are_same_file(G1, G4));
			Assert::IsTrue(squares_are_same_file(G1, G5));
			Assert::IsTrue(squares_are_same_file(G1, G6));
			Assert::IsTrue(squares_are_same_file(G1, G7));
			Assert::IsTrue(squares_are_same_file(G1, G8));
			
			Assert::IsTrue(squares_are_same_file(H1, H2));
			Assert::IsTrue(squares_are_same_file(H1, H3));
			Assert::IsTrue(squares_are_same_file(H1, H4));
			Assert::IsTrue(squares_are_same_file(H1, H5));
			Assert::IsTrue(squares_are_same_file(H1, H6));
			Assert::IsTrue(squares_are_same_file(H1, H7));
			Assert::IsTrue(squares_are_same_file(H1, H8));

			Assert::IsFalse(squares_are_same_file(A1, B1));
			Assert::IsFalse(squares_are_same_file(A1, C1));
			Assert::IsFalse(squares_are_same_file(G7, D1));
			Assert::IsFalse(squares_are_same_file(G7, F6));
			Assert::IsFalse(squares_are_same_file(G7, H7));
			Assert::IsFalse(squares_are_same_file(G7, F7));
		}
		TEST_METHOD(SquaresAreOnTheSameRank)
		{
			Assert::IsTrue(squares_are_on_the_same_rank(A1, B1));
			Assert::IsTrue(squares_are_on_the_same_rank(A1, C1));
			Assert::IsTrue(squares_are_on_the_same_rank(A1, D1));
			Assert::IsTrue(squares_are_on_the_same_rank(A1, E1));
			Assert::IsTrue(squares_are_on_the_same_rank(A1, F1));
			Assert::IsTrue(squares_are_on_the_same_rank(A1, G1));
			Assert::IsTrue(squares_are_on_the_same_rank(A1, H1));

			Assert::IsTrue(squares_are_on_the_same_rank(A2, B2));
			Assert::IsTrue(squares_are_on_the_same_rank(A2, C2));
			Assert::IsTrue(squares_are_on_the_same_rank(A2, D2));
			Assert::IsTrue(squares_are_on_the_same_rank(A2, E2));
			Assert::IsTrue(squares_are_on_the_same_rank(A2, F2));
			Assert::IsTrue(squares_are_on_the_same_rank(A2, G2));
			Assert::IsTrue(squares_are_on_the_same_rank(A2, H2));

			Assert::IsTrue(squares_are_on_the_same_rank(A3, B3));
			Assert::IsTrue(squares_are_on_the_same_rank(A3, C3));
			Assert::IsTrue(squares_are_on_the_same_rank(A3, D3));
			Assert::IsTrue(squares_are_on_the_same_rank(A3, E3));
			Assert::IsTrue(squares_are_on_the_same_rank(A3, F3));
			Assert::IsTrue(squares_are_on_the_same_rank(A3, G3));
			Assert::IsTrue(squares_are_on_the_same_rank(A3, H3));

			Assert::IsTrue(squares_are_on_the_same_rank(A4, B4));
			Assert::IsTrue(squares_are_on_the_same_rank(A4, C4));
			Assert::IsTrue(squares_are_on_the_same_rank(A4, D4));
			Assert::IsTrue(squares_are_on_the_same_rank(A4, E4));
			Assert::IsTrue(squares_are_on_the_same_rank(A4, F4));
			Assert::IsTrue(squares_are_on_the_same_rank(A4, G4));
			Assert::IsTrue(squares_are_on_the_same_rank(A4, H4));
			
			Assert::IsTrue(squares_are_on_the_same_rank(A5, B5));
			Assert::IsTrue(squares_are_on_the_same_rank(A5, C5));
			Assert::IsTrue(squares_are_on_the_same_rank(A5, D5));
			Assert::IsTrue(squares_are_on_the_same_rank(A5, E5));
			Assert::IsTrue(squares_are_on_the_same_rank(A5, F5));
			Assert::IsTrue(squares_are_on_the_same_rank(A5, G5));
			Assert::IsTrue(squares_are_on_the_same_rank(A5, H5));
			
			Assert::IsTrue(squares_are_on_the_same_rank(A6, B6));
			Assert::IsTrue(squares_are_on_the_same_rank(A6, C6));
			Assert::IsTrue(squares_are_on_the_same_rank(A6, D6));
			Assert::IsTrue(squares_are_on_the_same_rank(A6, E6));
			Assert::IsTrue(squares_are_on_the_same_rank(A6, F6));
			Assert::IsTrue(squares_are_on_the_same_rank(A6, G6));
			Assert::IsTrue(squares_are_on_the_same_rank(A6, H6));
			
			Assert::IsTrue(squares_are_on_the_same_rank(A7, B7));
			Assert::IsTrue(squares_are_on_the_same_rank(A7, C7));
			Assert::IsTrue(squares_are_on_the_same_rank(A7, D7));
			Assert::IsTrue(squares_are_on_the_same_rank(A7, E7));
			Assert::IsTrue(squares_are_on_the_same_rank(A7, F7));
			Assert::IsTrue(squares_are_on_the_same_rank(A7, G7));
			Assert::IsTrue(squares_are_on_the_same_rank(A7, H7));
			
			Assert::IsTrue(squares_are_on_the_same_rank(A8, B8));
			Assert::IsTrue(squares_are_on_the_same_rank(A8, C8));
			Assert::IsTrue(squares_are_on_the_same_rank(A8, D8));
			Assert::IsTrue(squares_are_on_the_same_rank(A8, E8));
			Assert::IsTrue(squares_are_on_the_same_rank(A8, F8));
			Assert::IsTrue(squares_are_on_the_same_rank(A8, G8));
			Assert::IsTrue(squares_are_on_the_same_rank(A8, H8));

			Assert::IsFalse(squares_are_on_the_same_rank(A1, A2));
			Assert::IsFalse(squares_are_on_the_same_rank(A1, A3));
			Assert::IsFalse(squares_are_on_the_same_rank(D4, D3));
			Assert::IsFalse(squares_are_on_the_same_rank(D4, D5));
			Assert::IsFalse(squares_are_on_the_same_rank(D4, C6));
		}
		TEST_METHOD(SquaresAreOnTheSameDiagonal)
		{
			Assert::IsTrue(squares_are_on_the_same_diagonal(A1, B2));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A1, C3));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A1, D4));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A1, E5));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A1, F6));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A1, G7));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A1, H8));

			Assert::IsTrue(squares_are_on_the_same_diagonal(A2, B3));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A2, C4));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A2, D5));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A2, E6));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A2, F7));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A2, G8));

			Assert::IsTrue(squares_are_on_the_same_diagonal(A3, B4));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A3, C5));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A3, D6));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A3, E7));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A3, F8));

			Assert::IsTrue(squares_are_on_the_same_diagonal(A4, B5));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A4, C6));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A4, D7));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A4, E8));

			Assert::IsTrue(squares_are_on_the_same_diagonal(A5, B6));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A5, C7));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A5, D8));
			
			Assert::IsTrue(squares_are_on_the_same_diagonal(A6, B7));
			Assert::IsTrue(squares_are_on_the_same_diagonal(A6, C8));

			Assert::IsTrue(squares_are_on_the_same_diagonal(E4, F5));
			Assert::IsTrue(squares_are_on_the_same_diagonal(E4, G6));
			Assert::IsTrue(squares_are_on_the_same_diagonal(E4, H7));
			Assert::IsTrue(squares_are_on_the_same_diagonal(E4, D3));
			Assert::IsTrue(squares_are_on_the_same_diagonal(E4, C2));
			Assert::IsTrue(squares_are_on_the_same_diagonal(E4, B1));
			Assert::IsTrue(squares_are_on_the_same_diagonal(E4, D5));
			Assert::IsTrue(squares_are_on_the_same_diagonal(E4, C6));
			Assert::IsTrue(squares_are_on_the_same_diagonal(E4, B7));
			Assert::IsTrue(squares_are_on_the_same_diagonal(E4, A8));
			Assert::IsTrue(squares_are_on_the_same_diagonal(E4, F3));
			Assert::IsTrue(squares_are_on_the_same_diagonal(E4, G2));
			
			Assert::IsFalse(squares_are_on_the_same_diagonal(E4, F2));
			Assert::IsFalse(squares_are_on_the_same_diagonal(E4, G1));
			Assert::IsFalse(squares_are_on_the_same_diagonal(E4, D2));
			Assert::IsFalse(squares_are_on_the_same_diagonal(E4, E2));
			Assert::IsFalse(squares_are_on_the_same_diagonal(E4, C5));
			Assert::IsFalse(squares_are_on_the_same_diagonal(E4, C4));
			Assert::IsFalse(squares_are_on_the_same_diagonal(E4, F6));
		}
		TEST_METHOD(SquaresBetweenTest)
		{
			Assert::IsTrue(
				squaresBetweenAreSame(
					get_squares_between(A1, A2),
					{
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE
					}
			));

			Assert::IsTrue(
				squaresBetweenAreSame(
					get_squares_between(SQUARE_NONE, A2),
					{
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE
					}
			));
			
			Assert::IsTrue(
				squaresBetweenAreSame(
					get_squares_between(A1, SQUARE_NONE),
					{
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE
					}
			));

			Assert::IsTrue(
				squaresBetweenAreSame(
					get_squares_between(SQUARE_NONE, SQUARE_NONE),
					{
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE
					}
			));
			
			Assert::IsTrue(
				squaresBetweenAreSame(
					get_squares_between(A1, A1),
					{
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE
					}
			));
			
			Assert::IsTrue(
				squaresBetweenAreSame(
					get_squares_between(A1, A3),
					{
						A2,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE
					}
			));

			Assert::IsTrue(
				squaresBetweenAreSame(
					get_squares_between(A1, C3),
					{
						B2,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE
					}
			));

			Assert::IsTrue(
				squaresBetweenAreSame(
					get_squares_between(B1, G6),
					{
						C2,
						D3,
						E4,
						F5,
						SQUARE_NONE,
						SQUARE_NONE
					}
			));

			Assert::IsTrue(
				squaresBetweenAreSame(
					get_squares_between(D3, B1),
					{
						C2,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE
					}
			));

			Assert::IsTrue(
				squaresBetweenAreSame(
					get_squares_between(D3, H7),
					{
						E4,
						F5,
						G6,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE
					}
			));
			
			Assert::IsTrue(
				squaresBetweenAreSame(
					get_squares_between(D3, A6),
					{
						C4,
						B5,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE
					}
			));

			Assert::IsTrue(
				squaresBetweenAreSame(
					get_squares_between(D3, F1),
					{
						E2,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE,
						SQUARE_NONE
					}
			));
		}
	};
}