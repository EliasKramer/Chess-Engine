#include "CppUnitTest.h"
#include "TestMethods.h"
#include "../ChessProjectV2/BitBoard.h"
#include "../ChessTestV2/TestMethods.h"
#include "../ChessProjectV2/ChessBoardTest.h"

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
			Assert::AreEqual(20, (int)numberOfMovesAfterDepth(board, 1));
		}
		TEST_METHOD(depth_2)
		{
			ChessBoard board(STARTING_FEN);
			Assert::AreEqual(400, (int)numberOfMovesAfterDepth(board, 2));
		}
		TEST_METHOD(depth_3)
		{
			ChessBoard board(STARTING_FEN);
			Assert::AreEqual(8902, (int)numberOfMovesAfterDepth(board, 3));
		}
		TEST_METHOD(depth_4)
		{
			ChessBoard board(STARTING_FEN);
			Assert::AreEqual(197281, (int)numberOfMovesAfterDepth(board, 4));
		}
		TEST_METHOD(depth_5)
		{
			ChessBoard board(STARTING_FEN);
			//Assert::AreEqual(4865609, (int)numberOfMovesAfterDepth(board, 5));
		}
	};
	TEST_CLASS(PerftOtherPositions)
	{
	public:
		TEST_METHOD(Kiwipete)
		{
			ChessBoard board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
			Assert::AreEqual(48, (int)numberOfMovesAfterDepth(board, 1));

			Assert::AreEqual(2039, (int)numberOfMovesAfterDepth(board, 2));
		}
	};
}