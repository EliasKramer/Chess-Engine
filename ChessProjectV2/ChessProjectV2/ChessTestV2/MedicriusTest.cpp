#include "../ChessProjectV2/Medicrius.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MedicriusTest
{
	TEST_CLASS(MedicriusTest)
	{
	public:
		TEST_METHOD(testEvaluation)
		{
			//https://www.chess.com/analysis
			Medicrius medicrius;

			//insufficient material
			ChessBoard board("8/7k/8/K7/8/8/8/8 w - - 0 1");
			Assert::AreEqual(0, medicrius.evaluate_board(board));
			
			//insufficient material
			board = ChessBoard("8/7k/8/K7/8/8/8/8 b - - 0 1");
			Assert::AreEqual(0, medicrius.evaluate_board(board));
			
			//stalemate
			board = ChessBoard("8/1q6/8/5k2/8/8/4r3/K7 w - - 0 1");
			Assert::AreEqual(0, medicrius.evaluate_board(board));
			
			//not stalemate
			board = ChessBoard("8/1q6/8/5k2/8/8/4r3/K7 b - - 0 1");
			Assert::AreNotEqual(0, medicrius.evaluate_board(board));

			//white wins
			board = ChessBoard("8/6k1/8/2K2QRR/8/8/8/8 b - - 0 1");
			Assert::AreEqual(WHITE_WIN_EVAL_VALUE, medicrius.evaluate_board(board));
			
			//black wins
			board = ChessBoard("8/6k1/4q3/2K1q3/4q3/8/8/8 w - - 0 1");
			Assert::AreEqual(BLACK_WIN_EVAL_VALUE, medicrius.evaluate_board(board));
			
			//50 move rule
			board = ChessBoard("4n3/6k1/8/8/7n/1KRB4/8/8 w - - 50 1");
			Assert::AreEqual(0, medicrius.evaluate_board(board));

			//starting pos is equal
			board = ChessBoard(STARTING_FEN);
			Assert::AreEqual(0, medicrius.evaluate_board(board));

			//test position difference
			board = ChessBoard("krn5/8/8/8/4N3/8/8/6RK w - - 0 1");
			Assert::IsTrue(0 < medicrius.evaluate_board(board));
		}
	};
}