#include "CppUnitTest.h"
#include <string>
#include "../ChessProjectV2/Move.h"

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
			Move m(white, castle_short);
			Assert::AreEqual((int)E1, (int)m.getStart());
			Assert::AreEqual((int)G1, (int)m.getDestination());

			m = Move(white, castle_long);
			Assert::AreEqual((int)E1, (int)m.getStart());
			Assert::AreEqual((int)C1, (int)m.getDestination());

			m = Move(black, castle_short);
			Assert::AreEqual((int)E8, (int)m.getStart());
			Assert::AreEqual((int)G8, (int)m.getDestination());

			m = Move(black, castle_long);
			Assert::AreEqual((int)E8, (int)m.getStart());
			Assert::AreEqual((int)C8, (int)m.getDestination());
		}
		TEST_METHOD(testBitBoardGenerationOfMove)
		{
			//TODO
			/*
			Move m(A1, A2);
			Assert::AreEqual(0x101ULL, m.getBBWithMoveDone());
			Assert::AreEqual((BB_SQUARE[A1] | BB_SQUARE[A2]), m.getBBWithMoveDone());

			m = Move(D2, E4);
			Assert::AreEqual(0x10000800ULL, m.getBBWithMoveDone());
			Assert::AreEqual((BB_SQUARE[D2] | BB_SQUARE[E4]), m.getBBWithMoveDone());

			MovePromote mp(A7, A8, ChessPiece(white, queen));
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
				MoveCastle mc(white, castle_long);
				mc.getBBWithMoveDone();

				Assert::Fail();
			}
			catch (const char* errorMsg)
			{
				Assert::IsTrue(errorMsg == "ERROR. A Caslting Move does not produce a Move Bitboard");
			}
			*/
		}
		TEST_METHOD(testMoveString)
		{
			Move m(A1, A2);
			Assert::IsTrue(m.get_string() == "a1a2");

			Move mp(D2, D1, white, promote_queen);
			Assert::IsTrue(mp.get_string() == "d2d1q");
			mp = Move(D2, D1, white, promote_rook);
			Assert::IsTrue(mp.get_string() == "d2d1r");
			mp = Move(D2, D1, white, promote_bishop);
			Assert::IsTrue(mp.get_string() == "d2d1b");
			mp = Move(D2, D1, white, promote_knight);
			Assert::IsTrue(mp.get_string() == "d2d1n");

			Move mc(white, castle_short);
			Assert::IsTrue(mc.get_string() == "O-O");
			mc = Move(white, castle_long);
			Assert::IsTrue(mc.get_string() == "O-O-O");
			mc = Move(black, castle_short);
			Assert::IsTrue(mc.get_string() == "O-O");
			mc = Move(black, castle_long);
			Assert::IsTrue(mc.get_string() == "O-O-O");
		}
		TEST_METHOD(testFlagsAndConstructor)
		{
			//normal move right
			Move m(A1, A2);
			Assert::IsTrue(normal == m.getFlag());

			//normal move wrong
			try 
			{
				Move m(A1, A3, white, normal);
				Assert::Fail();
			}
			catch (const std::invalid_argument& errorMsg)
			{
				Assert::IsTrue(
					errorMsg.what() ==
					std::string("Invalid flag for move (False constructor called)"));
			}

			//castle constructor right
			m = Move(white, castle_short);
			Assert::IsTrue(castle == m.getFlag());
			m = Move(white, castle_long);
			Assert::IsTrue(castle == m.getFlag());
			m = Move(black, castle_short);
			Assert::IsTrue(castle == m.getFlag());
			m = Move(black, castle_long);
			Assert::IsTrue(castle == m.getFlag());
			
			//castle constructor wrong
			try
			{
				Move m1(E1, G1, white, castle);
				Assert::Fail();
			}
			catch (const std::invalid_argument& errorMsg)
			{
				Assert::IsTrue(
					errorMsg.what() == 
					std::string("Invalid flag for move (False constructor called)"));
			}
			try
			{
				Move m1(E1, C1, castle);
				Assert::Fail();
			}
			catch (const std::invalid_argument& errorMsg)
			{
				Assert::IsTrue(
					errorMsg.what() == 
					std::string("Invalid flag for move (False constructor called)"));
			}

			//en passant right
			m = Move(D5, C6, en_passant);
			Assert::IsTrue(en_passant == m.getFlag());
			
			//en passant wrong
			try
			{
				Move m1(D5, C6, white, en_passant);
				Assert::Fail();
			}
			catch (const std::invalid_argument& errorMsg)
			{
				Assert::IsTrue(
					errorMsg.what() == 
					std::string("Invalid flag for move (False constructor called)"));
			}
			
			//promote right
			m = Move(D2, D1, white, promote_queen);
			Assert::IsTrue(promote_queen == m.getFlag());
			m = Move(D2, D1, white, promote_rook);
			Assert::IsTrue(promote_rook == m.getFlag());
			m = Move(D2, D1, white, promote_bishop);
			Assert::IsTrue(promote_bishop == m.getFlag());
			m = Move(D2, D1, white, promote_knight);
			Assert::IsTrue(promote_knight == m.getFlag());
			
			//promote wrong
			try
			{
				Move m1(D2, D1, promote_queen);
				Assert::Fail();
			}
			catch (const std::invalid_argument& errorMsg)
			{
				Assert::IsTrue(
					errorMsg.what() == 
					std::string("Invalid flag for move (False constructor called)"));
			}
		}
	};
}