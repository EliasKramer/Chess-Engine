#include "CppUnitTest.h"
#include "TestMethods.h"
#include "../ChessProjectV2/BitBoard.h"
#include "../ChessProjectV2/ChessBoardTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MoveGenerationTest
{
	TEST_CLASS(MoveGenerationTest)
	{
	public:
		TEST_METHOD(generatingKingMoves)
		{
			//king is e4
			//can move everywhere
			ChessBoardTest board("8/8/8/8/4K3/8/8/8 w -- - 0 1");

			UniqueMoveList moves = board.getPseudoLegalMoves();
			Assert::AreEqual(8, (int)moves.size());

			Assert::IsTrue(moveListContains(Move(E4, D5), moves));
			Assert::IsTrue(moveListContains(Move(E4, E5), moves));
			Assert::IsTrue(moveListContains(Move(E4, F5), moves));
			Assert::IsTrue(moveListContains(Move(E4, D4), moves));
			Assert::IsTrue(moveListContains(Move(E4, F4), moves));
			Assert::IsTrue(moveListContains(Move(E4, D3), moves));
			Assert::IsTrue(moveListContains(Move(E4, E3), moves));
			Assert::IsTrue(moveListContains(Move(E4, F3), moves));

			board = ChessBoardTest("K/8/8/8/8/k/p/8 w -- - 0 1");
			moves = board.getPseudoLegalMoves();
			Assert::AreEqual(3, (int)moves.size());

			Assert::IsTrue(moveListContains(Move(A8, B8), moves));
			Assert::IsTrue(moveListContains(Move(A8, A7), moves));
			Assert::IsTrue(moveListContains(Move(A8, B7), moves));
		}
		TEST_METHOD(generatingKnightMoves)
		{
			ChessBoardTest board("8/8/8/8/4N3/8/8/8 w -- - 0 1");

			UniqueMoveList moves = board.getPseudoLegalMoves();
			Assert::AreEqual(8, (int)moves.size());

			Assert::IsTrue(moveListContains(Move(E4, F6), moves));
			Assert::IsTrue(moveListContains(Move(E4, G5), moves));
			Assert::IsTrue(moveListContains(Move(E4, G3), moves));
			Assert::IsTrue(moveListContains(Move(E4, F2), moves));
			Assert::IsTrue(moveListContains(Move(E4, D2), moves));
			Assert::IsTrue(moveListContains(Move(E4, C3), moves));
			Assert::IsTrue(moveListContains(Move(E4, C5), moves));
			Assert::IsTrue(moveListContains(Move(E4, D6), moves));

			board = ChessBoardTest("8/8/8/8/8/8/1n6/8 b -- - 0 1");
			moves = board.getPseudoLegalMoves();
			Assert::AreEqual(4, (int)moves.size());

			Assert::IsTrue(moveListContains(Move(B2, A4), moves));
			Assert::IsTrue(moveListContains(Move(B2, C4), moves));
			Assert::IsTrue(moveListContains(Move(B2, D3), moves));
			Assert::IsTrue(moveListContains(Move(B2, D1), moves));

			board = ChessBoardTest("8/8/8/8/8/3p4/3B1n2/8 b - - 0 1");
			moves = board.getPseudoLegalMoves();
			Assert::AreEqual(5, (int)moves.size());
			
			Assert::IsTrue(moveListContains(Move(F2, D1), moves));
			Assert::IsTrue(moveListContains(Move(F2, E4), moves));
			Assert::IsTrue(moveListContains(Move(F2, G4), moves));
			Assert::IsTrue(moveListContains(Move(F2, H3), moves));
			Assert::IsTrue(moveListContains(Move(F2, H1), moves));
		}
	};
}