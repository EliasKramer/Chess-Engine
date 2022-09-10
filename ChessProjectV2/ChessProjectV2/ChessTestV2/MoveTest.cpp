#include "CppUnitTest.h"
#include <string>
#include "../ChessProjectV2/Move.h"
#include "../ChessProjectV2/MoveCastle.h"
#include "../ChessProjectV2/MoveEnPassant.h"
#include "../ChessProjectV2/MovePromote.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MoveTest
{
	TEST_CLASS(MoveTest)
	{
	public:

		TEST_METHOD(moveBasicFunctions)
		{
			Move m(A1, B3);
			Assert::IsTrue(A1 == m.getStart());
			Assert::IsTrue(B3 == m.getDestination());

			Move sameMove(A1, B3);
			Move differentStart(A2, B3);
			Move differentDestination(A1, B4);
			Move differentMove(A2, B4);

			Assert::IsTrue(m == sameMove);
			Assert::IsFalse(m == differentStart);
			Assert::IsFalse(m == differentDestination);
			Assert::IsFalse(m == differentMove);

			Assert::IsFalse(m != sameMove);
			Assert::IsTrue(m != differentStart);
			Assert::IsTrue(m != differentDestination);
			Assert::IsTrue(m != differentMove);
		}
		TEST_METHOD(testCastlingConstructor)
		{
			MoveCastle m(White, CastleShort);
			Assert::IsTrue(m.getStart() == E1);
			Assert::IsTrue(m.getDestination() == G1);
			Assert::IsTrue(m.getRookStart() == H1);
			Assert::IsTrue(m.getRookDest() == F1);

			m = MoveCastle(White, CastleLong);
			Assert::IsTrue(m.getStart() == E1);
			Assert::IsTrue(m.getDestination() == C1);
			Assert::IsTrue(m.getRookStart() == A1);
			Assert::IsTrue(m.getRookDest() == D1);

			m = MoveCastle(Black, CastleShort);
			Assert::IsTrue(m.getStart() == E8);
			Assert::IsTrue(m.getDestination() == G8);
			Assert::IsTrue(m.getRookStart() == H8);
			Assert::IsTrue(m.getRookDest() == F8);

			m = MoveCastle(Black, CastleLong);
			Assert::IsTrue(m.getStart() == E8);
			Assert::IsTrue(m.getDestination() == C8);
			Assert::IsTrue(m.getRookStart() == A8);
			Assert::IsTrue(m.getRookDest() == D8);
		}
		TEST_METHOD(testBitBoardGenerationOfMove)
		{
			Move m(A1, A2);
			Assert::AreEqual(0x101ULL, m.getBBWithMoveDone());
			Assert::AreEqual((BB_SQUARE[A1] | BB_SQUARE[A2]), m.getBBWithMoveDone());

			m = Move(D2, E4);
			Assert::AreEqual(0x10000800ULL, m.getBBWithMoveDone());
			Assert::AreEqual((BB_SQUARE[D2] | BB_SQUARE[E4]), m.getBBWithMoveDone());

			MovePromote mp(A7, A8, ChessPiece(White, Queen));
			m = Move(A7, A8);
			Assert::AreEqual(m.getBBWithMoveDone(), mp.getBBWithMoveDone());
			Assert::AreEqual(0x101000000000000ULL, mp.getBBWithMoveDone());
			Assert::AreEqual((BB_SQUARE[A7] | BB_SQUARE[A8]), mp.getBBWithMoveDone());

			MoveEnPassant me(D5, E6, E5);
			m = Move(D5, E6);
			Assert::AreNotEqual(m.getBBWithMoveDone(), me.getBBWithMoveDone());
			Assert::AreEqual(0x101800000000ULL, me.getBBWithMoveDone());
			Assert::AreEqual((BB_SQUARE[D5] | BB_SQUARE[E6] | BB_SQUARE[E5]),
				me.getBBWithMoveDone());

			try
			{
				MoveCastle mc(White, CastleLong);
				mc.getBBWithMoveDone();

				Assert::Fail();
			}
			catch (const char* errorMsg)
			{
				Assert::IsTrue(errorMsg == "ERROR. A Caslting Move does not produce a Move Bitboard");
			}
		}
		TEST_METHOD(testMoveString)
		{
			Move m(A1, A2);
			Assert::IsTrue(m.getString() == "a1a2");

			MovePromote mp(D2, D1, ChessPiece(White, Queen));
			Assert::IsTrue(mp.getString() == "d2d1q");
			mp = MovePromote(D2, D1, ChessPiece(White, Rook));
			Assert::IsTrue(mp.getString() == "d2d1r");
			mp = MovePromote(D2, D1, ChessPiece(White, Bishop));
			Assert::IsTrue(mp.getString() == "d2d1b");
			mp = MovePromote(D2, D1, ChessPiece(White, Knight));
			Assert::IsTrue(mp.getString() == "d2d1n");
		}
	};
}