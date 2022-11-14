#include "CppUnitTest.h"
#include "TestMethods.h"
#include "../ChessProjectV2/BitBoard.h"
#include "../ChessTestV2/TestMethods.h"
#include "../ChessProjectV2/ChessBoardTest.h"
#include <vector>
#include <string>
#include <utility>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//See performance test results yourself
//https://www.chessprogramming.org/Perft_Results

namespace PerformanceTest
{
	TEST_CLASS(PerftStartPos)
	{
	public:
		TEST_METHOD(depth_1)
		{
			ChessBoard board(STARTING_FEN);
			Assert::AreEqual(20, (int)number_of_moves_after_depth(board, 1));
		}
		TEST_METHOD(depth_2)
		{
			ChessBoard board(STARTING_FEN);
			Assert::AreEqual(400, (int)number_of_moves_after_depth(board, 2));
		}
		TEST_METHOD(depth_3)
		{
			ChessBoard board(STARTING_FEN);
			Assert::AreEqual(8902, (int)number_of_moves_after_depth(board, 3));
		}
		TEST_METHOD(depth_4)
		{
			ChessBoard board(STARTING_FEN);
			Assert::AreEqual(197281, (int)number_of_moves_after_depth(board, 4));
		}
		TEST_METHOD(depth_5)
		{
			ChessBoard board(STARTING_FEN);
			//Assert::AreEqual(4865609, (int)number_of_moves_after_depth(board, 5));
		}
	};
	TEST_CLASS(PerftOtherPositions)
	{
	public:
		TEST_METHOD(kiwipete)
		{
			ChessBoard board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
			Assert::AreEqual(48, (int)number_of_moves_after_depth(board, 1));

			Assert::AreEqual(2039, (int)number_of_moves_after_depth(board, 2));

			Assert::AreEqual(97862, (int)number_of_moves_after_depth(board, 3));

			//uncomment for depth 4, but it will take around 18s longer
			//Assert::AreEqual(4085603, (int)number_of_moves_after_depth(board, 4));

			MoveList movesAtDepth1 = get_all_moves_at_depth(board, 1);
			MoveList movesAtDepth2 = get_all_moves_at_depth(board, 2);
			MoveList movesAtDepth3 = get_all_moves_at_depth(board, 3);
			//check en passant moves
			Assert::AreEqual(1, get_number_of_en_passant_moves(movesAtDepth2));
			Assert::AreEqual(45, get_number_of_en_passant_moves(movesAtDepth3));

			//check promotion moves
			Assert::AreEqual(0, get_number_of_promotion_moves(movesAtDepth1));
			Assert::AreEqual(0, get_number_of_promotion_moves(movesAtDepth2));
			Assert::AreEqual(0, get_number_of_promotion_moves(movesAtDepth3));

			//check castle moves
			Assert::AreEqual(2, get_number_of_castling_moves(movesAtDepth1));
			Assert::AreEqual(91, get_number_of_castling_moves(movesAtDepth2));
			Assert::AreEqual(3162, get_number_of_castling_moves(movesAtDepth3));
		}
		//the name test pos 3 is from the chess programming wiki,
		//i wont come up with such creative ideas
		TEST_METHOD(test_pos_3)
		{
			ChessBoard board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
			Assert::AreEqual(14, (int)number_of_moves_after_depth(board, 1));
			Assert::AreEqual(191, (int)number_of_moves_after_depth(board, 2));
			Assert::AreEqual(2812, (int)number_of_moves_after_depth(board, 3));
			Assert::AreEqual(43238, (int)number_of_moves_after_depth(board, 4));

			//uncomment more tests - commented for more testing speed
			//Assert::AreEqual(674624, (int)number_of_moves_after_depth(board, 5));
			//Assert::AreEqual(11030083, (int)number_of_moves_after_depth(board, 6));
		}
		TEST_METHOD(test_pos_4)
		{
			ChessBoard board("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
			Assert::AreEqual(6, (int)number_of_moves_after_depth(board, 1));
			Assert::AreEqual(264, (int)number_of_moves_after_depth(board, 2));
			Assert::AreEqual(9467, (int)number_of_moves_after_depth(board, 3));
			Assert::AreEqual(422333, (int)number_of_moves_after_depth(board, 4));
			//Assert::AreEqual(15833292, (int)number_of_moves_after_depth(board, 5));

			MoveList movesAtDepth1 = get_all_moves_at_depth(board, 1);
			MoveList movesAtDepth2 = get_all_moves_at_depth(board, 2);
			MoveList movesAtDepth3 = get_all_moves_at_depth(board, 3);
			MoveList movesAtDepth4 = get_all_moves_at_depth(board, 4);
			// 
			//check en passant moves
			Assert::AreEqual(0, get_number_of_en_passant_moves(movesAtDepth1));
			Assert::AreEqual(0, get_number_of_en_passant_moves(movesAtDepth2));
			Assert::AreEqual(4, get_number_of_en_passant_moves(movesAtDepth3));
			Assert::AreEqual(0, get_number_of_en_passant_moves(movesAtDepth4));

			//check promotion moves
			Assert::AreEqual(0, get_number_of_promotion_moves(movesAtDepth1));
			Assert::AreEqual(48, get_number_of_promotion_moves(movesAtDepth2));
			Assert::AreEqual(120, get_number_of_promotion_moves(movesAtDepth3));
			Assert::AreEqual(60032, get_number_of_promotion_moves(movesAtDepth4));

			//check castle moves
			Assert::AreEqual(0, get_number_of_castling_moves(movesAtDepth1));
			Assert::AreEqual(6, get_number_of_castling_moves(movesAtDepth2));
			Assert::AreEqual(0, get_number_of_castling_moves(movesAtDepth3));
			Assert::AreEqual(7795, get_number_of_castling_moves(movesAtDepth4));
		}
		TEST_METHOD(test_pos_5)
		{
			ChessBoard board("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");
			Assert::AreEqual(44, (int)number_of_moves_after_depth(board, 1));
			Assert::AreEqual(1486, (int)number_of_moves_after_depth(board, 2));
			Assert::AreEqual(62379, (int)number_of_moves_after_depth(board, 3));
			//Assert::AreEqual(2103487, (int)number_of_moves_after_depth(board, 4));
			//Assert::AreEqual(89941194, (int)number_of_moves_after_depth(board, 5));
		}
		TEST_METHOD(test_pos_6)
		{
			ChessBoard board("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
			Assert::AreEqual(46, (int)number_of_moves_after_depth(board, 1));
			Assert::AreEqual(2079, (int)number_of_moves_after_depth(board, 2));
			Assert::AreEqual(89890, (int)number_of_moves_after_depth(board, 3));
			//Assert::AreEqual(3894594, (int)number_of_moves_after_depth(board, 4));
			//Assert::AreEqual(164075551, (int)number_of_moves_after_depth(board, 5));
		}
	};
}