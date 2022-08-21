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
			//
			
			board = ChessBoardTest("K/8/8/8/8/k/p/8 w -- - 0 1");
			moves = board.getPseudoLegalMoves();
			Assert::AreEqual(3, (int)moves.size());

			
		}
	};
}