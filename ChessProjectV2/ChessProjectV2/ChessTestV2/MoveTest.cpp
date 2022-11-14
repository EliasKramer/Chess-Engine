#include "CppUnitTest.h"
#include <string>
#include "../ChessProjectV2/Move.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MoveTest
{
	TEST_CLASS(MoveTest)
	{
	public:

		TEST_METHOD(move_basic_functions)
		{
			Move m(A1, B3);
			Assert::IsTrue(A1 == m.get_start());
			Assert::IsTrue(B3 == m.get_destination());

			Move same_move(A1, B3);
			Move different_start(A2, B3);
			Move different_destination(A1, B4);
			Move different_move(A2, B4);

			Assert::IsTrue(m == same_move);
			Assert::IsFalse(m == different_start);
			Assert::IsFalse(m == different_destination);
			Assert::IsFalse(m == different_move);

			Assert::IsFalse(m != same_move);
			Assert::IsTrue(m != different_start);
			Assert::IsTrue(m != different_destination);
			Assert::IsTrue(m != different_move);
		}
		TEST_METHOD(castling_constructor)
		{
			Move m(white, castle_short);
			Assert::AreEqual((int)E1, (int)m.get_start());
			Assert::AreEqual((int)G1, (int)m.get_destination());

			m = Move(white, castle_long);
			Assert::AreEqual((int)E1, (int)m.get_start());
			Assert::AreEqual((int)C1, (int)m.get_destination());

			m = Move(black, castle_short);
			Assert::AreEqual((int)E8, (int)m.get_start());
			Assert::AreEqual((int)G8, (int)m.get_destination());

			m = Move(black, castle_long);
			Assert::AreEqual((int)E8, (int)m.get_start());
			Assert::AreEqual((int)C8, (int)m.get_destination());
		}
		TEST_METHOD(bitboard_generation_of_move)
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
			catch (const char* error_msg)
			{
				Assert::IsTrue(error_msg == "ERROR. A Caslting Move does not produce a Move Bitboard");
			}
			*/
		}
		TEST_METHOD(test_move_string)
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
		TEST_METHOD(test_flags_and_constructor)
		{
			//normal move right
			Move m(A1, A2);
			Assert::IsTrue(normal == m.get_flag());

			//normal move wrong
			try 
			{
				Move m(A1, A3, white, normal);
				Assert::Fail();
			}
			catch (const std::invalid_argument& error_msg)
			{
				Assert::IsTrue(
					error_msg.what() ==
					std::string("Invalid flag for move (False constructor called)"));
			}

			//castle constructor right
			m = Move(white, castle_short);
			Assert::IsTrue(castle == m.get_flag());
			m = Move(white, castle_long);
			Assert::IsTrue(castle == m.get_flag());
			m = Move(black, castle_short);
			Assert::IsTrue(castle == m.get_flag());
			m = Move(black, castle_long);
			Assert::IsTrue(castle == m.get_flag());
			
			//castle constructor wrong
			try
			{
				Move m1(E1, G1, white, castle);
				Assert::Fail();
			}
			catch (const std::invalid_argument& error_msg)
			{
				Assert::IsTrue(
					error_msg.what() == 
					std::string("Invalid flag for move (False constructor called)"));
			}
			try
			{
				Move m1(E1, C1, castle);
				Assert::Fail();
			}
			catch (const std::invalid_argument& error_msg)
			{
				Assert::IsTrue(
					error_msg.what() == 
					std::string("Invalid flag for move (False constructor called)"));
			}

			//en passant right
			m = Move(D5, C6, en_passant);
			Assert::IsTrue(en_passant == m.get_flag());
			
			//en passant wrong
			try
			{
				Move m1(D5, C6, white, en_passant);
				Assert::Fail();
			}
			catch (const std::invalid_argument& error_msg)
			{
				Assert::IsTrue(
					error_msg.what() == 
					std::string("Invalid flag for move (False constructor called)"));
			}
			
			//promote right
			m = Move(D2, D1, white, promote_queen);
			Assert::IsTrue(promote_queen == m.get_flag());
			m = Move(D2, D1, white, promote_rook);
			Assert::IsTrue(promote_rook == m.get_flag());
			m = Move(D2, D1, white, promote_bishop);
			Assert::IsTrue(promote_bishop == m.get_flag());
			m = Move(D2, D1, white, promote_knight);
			Assert::IsTrue(promote_knight == m.get_flag());
			
			//promote wrong
			try
			{
				Move m1(D2, D1, promote_queen);
				Assert::Fail();
			}
			catch (const std::invalid_argument& error_msg)
			{
				Assert::IsTrue(
					error_msg.what() == 
					std::string("Invalid flag for move (False constructor called)"));
			}
		}
	};
}