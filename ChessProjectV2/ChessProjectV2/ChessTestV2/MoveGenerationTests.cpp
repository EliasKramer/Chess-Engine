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
		TEST_METHOD(generatingPawnMoves)
		{
			//only forward moves
			//black pawns on e7 g6 c5
			//white pawns on e2 h3

			//white to move
			ChessBoardTest board("8/4p3/6p1/2p5/8/7P/4P3/8 w -- - 0 1");

			UniqueMoveList moves = board.getPseudoLegalMoves();
			Assert::AreEqual(3, (int)moves.size());
			Assert::IsTrue(moveListContains(Move(E2, E3), moves));
			Assert::IsTrue(moveListContains(Move(E2, E4), moves));
			Assert::IsTrue(moveListContains(Move(H3, H4), moves));

			//black to move
			board = ChessBoardTest("8/4p3/6p1/2p5/8/7P/4P3/8 b -- - 0 1");

			moves = board.getPseudoLegalMoves();
			Assert::AreEqual(4, (int)moves.size());
			Assert::IsTrue(moveListContains(Move(E7, E6), moves));
			Assert::IsTrue(moveListContains(Move(E7, E5), moves));
			Assert::IsTrue(moveListContains(Move(G6, G5), moves));
			Assert::IsTrue(moveListContains(Move(C5, C4), moves));

			//white has no move. black is blocking the move
			board = ChessBoardTest("8/8/8/8/8/2p5/2P5/8 w - - 0 1");

			moves = board.getPseudoLegalMoves();
			Assert::AreEqual(0, (int)moves.size());

			//black can take white's Rook
			//pawn on h7 
			//rook on g6
			board = ChessBoardTest("8/7p/6R1/8/8/8/8/8 b - - 0 1");

			moves = board.getPseudoLegalMoves();
			Assert::AreEqual(3, (int)moves.size());
			Assert::IsTrue(moveListContains(Move(H7, G6), moves));
			Assert::IsTrue(moveListContains(Move(H7, H6), moves));
			Assert::IsTrue(moveListContains(Move(H7, H5), moves));

			//white can take blacks pieces
			//white pawn is on e4
			//black knight is on d5
			//black rook is on f5
			board = ChessBoardTest("8/8/8/3n1r2/4P3/8/8/8 w - - 0 1");

			moves = board.getPseudoLegalMoves();
			Assert::AreEqual(3, (int)moves.size());
			Assert::IsTrue(moveListContains(Move(E4, D5), moves));
			Assert::IsTrue(moveListContains(Move(E4, F5), moves));
			Assert::IsTrue(moveListContains(Move(E4, E5), moves));
		}
		TEST_METHOD(generatingRookMoves)
		{
			//white rook on a1
			//white rook on h1
			//black rook on a8
			//black rook on h8
			ChessBoardTest board("r6r/8/8/8/8/8/8/R6R w - - 0 1");
			UniqueMoveList moves = board.getPseudoLegalMoves();
			Assert::AreEqual(26, (int)moves.size());

			//first rook

			//moves towards same-colored rook
			Assert::IsTrue(moveListContains(Move(A1, B1), moves));
			Assert::IsTrue(moveListContains(Move(A1, C1), moves));
			Assert::IsTrue(moveListContains(Move(A1, D1), moves));
			Assert::IsTrue(moveListContains(Move(A1, E1), moves));
			Assert::IsTrue(moveListContains(Move(A1, F1), moves));
			Assert::IsTrue(moveListContains(Move(A1, G1), moves));

			//moves towards opposite-colored rook
			Assert::IsTrue(moveListContains(Move(A1, A2), moves));
			Assert::IsTrue(moveListContains(Move(A1, A3), moves));
			Assert::IsTrue(moveListContains(Move(A1, A4), moves));
			Assert::IsTrue(moveListContains(Move(A1, A5), moves));
			Assert::IsTrue(moveListContains(Move(A1, A6), moves));
			Assert::IsTrue(moveListContains(Move(A1, A7), moves));
			Assert::IsTrue(moveListContains(Move(A1, A8), moves));

			//second rook

			//moves towards same-colored rook
			Assert::IsTrue(moveListContains(Move(H1, G1), moves));
			Assert::IsTrue(moveListContains(Move(H1, F1), moves));
			Assert::IsTrue(moveListContains(Move(H1, E1), moves));
			Assert::IsTrue(moveListContains(Move(H1, D1), moves));
			Assert::IsTrue(moveListContains(Move(H1, C1), moves));
			Assert::IsTrue(moveListContains(Move(H1, B1), moves));

			//moves towards opposite-colored rook
			Assert::IsTrue(moveListContains(Move(H1, H2), moves));
			Assert::IsTrue(moveListContains(Move(H1, H3), moves));
			Assert::IsTrue(moveListContains(Move(H1, H4), moves));
			Assert::IsTrue(moveListContains(Move(H1, H5), moves));
			Assert::IsTrue(moveListContains(Move(H1, H6), moves));
			Assert::IsTrue(moveListContains(Move(H1, H7), moves));
			Assert::IsTrue(moveListContains(Move(H1, H8), moves));

			board = ChessBoardTest("r6r/8/8/8/8/8/8/R6R b - - 0 1");
			moves = board.getPseudoLegalMoves();

			Assert::AreEqual(26, (int)moves.size());

			//first rook

			//moves towards same-colored rook
			Assert::IsTrue(moveListContains(Move(A8, B8), moves));
			Assert::IsTrue(moveListContains(Move(A8, C8), moves));
			Assert::IsTrue(moveListContains(Move(A8, D8), moves));
			Assert::IsTrue(moveListContains(Move(A8, E8), moves));
			Assert::IsTrue(moveListContains(Move(A8, F8), moves));
			Assert::IsTrue(moveListContains(Move(A8, G8), moves));

			//moves towards opposite-colored rook
			Assert::IsTrue(moveListContains(Move(A8, A7), moves));
			Assert::IsTrue(moveListContains(Move(A8, A6), moves));
			Assert::IsTrue(moveListContains(Move(A8, A5), moves));
			Assert::IsTrue(moveListContains(Move(A8, A4), moves));
			Assert::IsTrue(moveListContains(Move(A8, A3), moves));
			Assert::IsTrue(moveListContains(Move(A8, A2), moves));
			Assert::IsTrue(moveListContains(Move(A8, A1), moves));

			//second rook

			//moves towards same-colored rook
			Assert::IsTrue(moveListContains(Move(H8, G8), moves));
			Assert::IsTrue(moveListContains(Move(H8, F8), moves));
			Assert::IsTrue(moveListContains(Move(H8, E8), moves));
			Assert::IsTrue(moveListContains(Move(H8, D8), moves));
			Assert::IsTrue(moveListContains(Move(H8, C8), moves));
			Assert::IsTrue(moveListContains(Move(H8, B8), moves));

			//moves towards opposite-colored rook
			Assert::IsTrue(moveListContains(Move(H8, H7), moves));
			Assert::IsTrue(moveListContains(Move(H8, H6), moves));
			Assert::IsTrue(moveListContains(Move(H8, H5), moves));
			Assert::IsTrue(moveListContains(Move(H8, H4), moves));
			Assert::IsTrue(moveListContains(Move(H8, H3), moves));
			Assert::IsTrue(moveListContains(Move(H8, H2), moves));
			Assert::IsTrue(moveListContains(Move(H8, H1), moves));

			//gets 0 moves when blocked completely
			board = ChessBoardTest("8/8/8/7p/6pP/6PR/7P/8 w - - 0 1");
			moves = board.getPseudoLegalMoves();

			Assert::AreEqual(0, (int)moves.size());
		}
		TEST_METHOD(generatingBishopMoves)
		{
			ChessBoardTest board("8/8/1p6/8/3B4/8/8/B7 w - - 0 1");
			UniqueMoveList moves = board.getPseudoLegalMoves();
			Assert::AreEqual(13, (int)moves.size());

			//first bishop
			Assert::IsTrue(moveListContains(Move(A1, B2), moves));
			Assert::IsTrue(moveListContains(Move(A1, C3), moves));

			//second bishop
			Assert::IsTrue(moveListContains(Move(D4, C3), moves));
			Assert::IsTrue(moveListContains(Move(D4, B2), moves));

			Assert::IsTrue(moveListContains(Move(D4, C5), moves));
			Assert::IsTrue(moveListContains(Move(D4, B6), moves));

			Assert::IsTrue(moveListContains(Move(D4, E5), moves));
			Assert::IsTrue(moveListContains(Move(D4, F6), moves));
			Assert::IsTrue(moveListContains(Move(D4, G7), moves));
			Assert::IsTrue(moveListContains(Move(D4, H8), moves));

			Assert::IsTrue(moveListContains(Move(D4, E3), moves));
			Assert::IsTrue(moveListContains(Move(D4, F2), moves));
			Assert::IsTrue(moveListContains(Move(D4, G1), moves));
		}
		TEST_METHOD(generatingQueenMoves)
		{
			ChessBoardTest board("8/8/6p1/6P1/8/1n2Q3/8/8 w - - 0 1");
			
			UniqueMoveList moves = board.getPseudoLegalMoves();
			Assert::AreEqual(22, (int)moves.size());
			
			Assert::IsTrue(moveListContains(Move(E3, E4), moves));
			Assert::IsTrue(moveListContains(Move(E3, E5), moves));
			Assert::IsTrue(moveListContains(Move(E3, E6), moves));
			Assert::IsTrue(moveListContains(Move(E3, E7), moves));
			Assert::IsTrue(moveListContains(Move(E3, E8), moves));

			Assert::IsTrue(moveListContains(Move(E3, F4), moves));
			
			Assert::IsTrue(moveListContains(Move(E3, F3), moves));
			Assert::IsTrue(moveListContains(Move(E3, G3), moves));
			Assert::IsTrue(moveListContains(Move(E3, H3), moves));

			Assert::IsTrue(moveListContains(Move(E3, F2), moves));
			Assert::IsTrue(moveListContains(Move(E3, G1), moves));

			Assert::IsTrue(moveListContains(Move(E3, E2), moves));
			Assert::IsTrue(moveListContains(Move(E3, E1), moves));
			
			Assert::IsTrue(moveListContains(Move(E3, D2), moves));
			Assert::IsTrue(moveListContains(Move(E3, C1), moves));

			Assert::IsTrue(moveListContains(Move(E3, D3), moves));
			Assert::IsTrue(moveListContains(Move(E3, C3), moves));

			Assert::IsTrue(moveListContains(Move(E3, D4), moves));
			Assert::IsTrue(moveListContains(Move(E3, C5), moves));
			Assert::IsTrue(moveListContains(Move(E3, B6), moves));
			Assert::IsTrue(moveListContains(Move(E3, A7), moves));
		}
	};
}