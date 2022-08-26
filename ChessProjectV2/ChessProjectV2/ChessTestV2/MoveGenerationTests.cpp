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

			MoveList moves = board.getPseudoLegalMoves();
			Assert::AreEqual(8, (int)moves.size());

			Assert::IsTrue(moveListContains(Move(E4, D5, King), moves));
			Assert::IsTrue(moveListContains(Move(E4, E5, King), moves));
			Assert::IsTrue(moveListContains(Move(E4, F5, King), moves));
			Assert::IsTrue(moveListContains(Move(E4, D4, King), moves));
			Assert::IsTrue(moveListContains(Move(E4, F4, King), moves));
			Assert::IsTrue(moveListContains(Move(E4, D3, King), moves));
			Assert::IsTrue(moveListContains(Move(E4, E3, King), moves));
			Assert::IsTrue(moveListContains(Move(E4, F3, King), moves));

			board = ChessBoardTest("K/8/8/8/8/k/p/8 w -- - 0 1");
			moves = board.getPseudoLegalMoves();
			Assert::AreEqual(3, (int)moves.size());

			Assert::IsTrue(moveListContains(Move(A8, B8, King), moves));
			Assert::IsTrue(moveListContains(Move(A8, A7, King), moves));
			Assert::IsTrue(moveListContains(Move(A8, B7, King), moves));
		}
		TEST_METHOD(generatingKnightMoves)
		{
			ChessBoardTest board("8/8/8/8/4N3/8/8/8 w -- - 0 1");

			MoveList moves = board.getPseudoLegalMoves();
			Assert::AreEqual(8, (int)moves.size());

			Assert::IsTrue(moveListContains(Move(E4, F6, Knight), moves));
			Assert::IsTrue(moveListContains(Move(E4, G5, Knight), moves));
			Assert::IsTrue(moveListContains(Move(E4, G3, Knight), moves));
			Assert::IsTrue(moveListContains(Move(E4, F2, Knight), moves));
			Assert::IsTrue(moveListContains(Move(E4, D2, Knight), moves));
			Assert::IsTrue(moveListContains(Move(E4, C3, Knight), moves));
			Assert::IsTrue(moveListContains(Move(E4, C5, Knight), moves));
			Assert::IsTrue(moveListContains(Move(E4, D6, Knight), moves));

			board = ChessBoardTest("8/8/8/8/8/8/1n6/8 b -- - 0 1");
			moves = board.getPseudoLegalMoves();
			Assert::AreEqual(4, (int)moves.size());

			Assert::IsTrue(moveListContains(Move(B2, A4, Knight), moves));
			Assert::IsTrue(moveListContains(Move(B2, C4, Knight), moves));
			Assert::IsTrue(moveListContains(Move(B2, D3, Knight), moves));
			Assert::IsTrue(moveListContains(Move(B2, D1, Knight), moves));

			board = ChessBoardTest("8/8/8/8/8/3p4/3B1n2/8 b - - 0 1");
			moves = board.getPseudoLegalMoves();
			Assert::AreEqual(5, (int)moves.size());

			Assert::IsTrue(moveListContains(Move(F2, D1, Knight), moves));
			Assert::IsTrue(moveListContains(Move(F2, E4, Knight), moves));
			Assert::IsTrue(moveListContains(Move(F2, G4, Knight), moves));
			Assert::IsTrue(moveListContains(Move(F2, H3, Knight), moves));
			Assert::IsTrue(moveListContains(Move(F2, H1, Knight), moves));
		}
		TEST_METHOD(generatingPawnMoves)
		{
			//only forward moves
			//black pawns on e7 g6 c5
			//white pawns on e2 h3

			//white to move
			ChessBoardTest board("8/4p3/6p1/2p5/8/7P/4P3/8 w -- - 0 1");

			MoveList moves = board.getPseudoLegalMoves();
			Assert::AreEqual(3, (int)moves.size());
			Assert::IsTrue(moveListContains(Move(E2, E3, Pawn), moves));
			Assert::IsTrue(moveListContains(Move(E2, E4, Pawn), moves));
			Assert::IsTrue(moveListContains(Move(H3, H4, Pawn), moves));

			//black to move
			board = ChessBoardTest("8/4p3/6p1/2p5/8/7P/4P3/8 b -- - 0 1");

			moves = board.getPseudoLegalMoves();
			Assert::AreEqual(4, (int)moves.size());
			Assert::IsTrue(moveListContains(Move(E7, E6, Pawn), moves));
			Assert::IsTrue(moveListContains(Move(E7, E5, Pawn), moves));
			Assert::IsTrue(moveListContains(Move(G6, G5, Pawn), moves));
			Assert::IsTrue(moveListContains(Move(C5, C4, Pawn), moves));

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
			Assert::IsTrue(moveListContains(Move(H7, G6, Pawn), moves));
			Assert::IsTrue(moveListContains(Move(H7, H6, Pawn), moves));
			Assert::IsTrue(moveListContains(Move(H7, H5, Pawn), moves));

			//white can take blacks pieces
			//white pawn is on e4
			//black knight is on d5
			//black rook is on f5
			board = ChessBoardTest("8/8/8/3n1r2/4P3/8/8/8 w - - 0 1");

			moves = board.getPseudoLegalMoves();
			Assert::AreEqual(3, (int)moves.size());
			Assert::IsTrue(moveListContains(Move(E4, D5, Pawn), moves));
			Assert::IsTrue(moveListContains(Move(E4, F5, Pawn), moves));
			Assert::IsTrue(moveListContains(Move(E4, E5, Pawn), moves));
		}
		TEST_METHOD(generatingRookMoves)
		{
			//white rook on a1
			//white rook on h1
			//black rook on a8
			//black rook on h8
			ChessBoardTest board("r6r/8/8/8/8/8/8/R6R w - - 0 1");
			MoveList moves = board.getPseudoLegalMoves();
			Assert::AreEqual(26, (int)moves.size());

			//first rook

			//moves towards same-colored rook
			Assert::IsTrue(moveListContains(Move(A1, B1, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A1, C1, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A1, D1, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A1, E1, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A1, F1, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A1, G1, Rook), moves));

			//moves towards opposite-colored rook
			Assert::IsTrue(moveListContains(Move(A1, A2, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A1, A3, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A1, A4, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A1, A5, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A1, A6, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A1, A7, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A1, A8, Rook), moves));

			//second rook

			//moves towards same-colored rook
			Assert::IsTrue(moveListContains(Move(H1, G1, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H1, F1, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H1, E1, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H1, D1, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H1, C1, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H1, B1, Rook), moves));

			//moves towards opposite-colored rook
			Assert::IsTrue(moveListContains(Move(H1, H2, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H1, H3, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H1, H4, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H1, H5, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H1, H6, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H1, H7, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H1, H8, Rook), moves));

			board = ChessBoardTest("r6r/8/8/8/8/8/8/R6R b - - 0 1");
			moves = board.getPseudoLegalMoves();

			Assert::AreEqual(26, (int)moves.size());

			//first rook

			//moves towards same-colored rook
			Assert::IsTrue(moveListContains(Move(A8, B8, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A8, C8, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A8, D8, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A8, E8, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A8, F8, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A8, G8, Rook), moves));

			//moves towards opposite-colored rook
			Assert::IsTrue(moveListContains(Move(A8, A7, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A8, A6, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A8, A5, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A8, A4, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A8, A3, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A8, A2, Rook), moves));
			Assert::IsTrue(moveListContains(Move(A8, A1, Rook), moves));

			//second rook

			//moves towards same-colored rook
			Assert::IsTrue(moveListContains(Move(H8, G8, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H8, F8, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H8, E8, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H8, D8, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H8, C8, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H8, B8, Rook), moves));

			//moves towards opposite-colored rook
			Assert::IsTrue(moveListContains(Move(H8, H7, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H8, H6, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H8, H5, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H8, H4, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H8, H3, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H8, H2, Rook), moves));
			Assert::IsTrue(moveListContains(Move(H8, H1, Rook), moves));

			//gets 0 moves when blocked completely
			board = ChessBoardTest("8/8/8/7p/6pP/6PR/7P/8 w - - 0 1");
			moves = board.getPseudoLegalMoves();

			Assert::AreEqual(0, (int)moves.size());
		}
		TEST_METHOD(generatingBishopMoves)
		{
			ChessBoardTest board("8/8/1p6/8/3B4/8/8/B7 w - - 0 1");
			MoveList moves = board.getPseudoLegalMoves();
			Assert::AreEqual(13, (int)moves.size());

			//first bishop
			Assert::IsTrue(moveListContains(Move(A1, B2, Bishop), moves));
			Assert::IsTrue(moveListContains(Move(A1, C3, Bishop), moves));

			//second bishop
			Assert::IsTrue(moveListContains(Move(D4, C3, Bishop), moves));
			Assert::IsTrue(moveListContains(Move(D4, B2, Bishop), moves));

			Assert::IsTrue(moveListContains(Move(D4, C5, Bishop), moves));
			Assert::IsTrue(moveListContains(Move(D4, B6, Bishop), moves));

			Assert::IsTrue(moveListContains(Move(D4, E5, Bishop), moves));
			Assert::IsTrue(moveListContains(Move(D4, F6, Bishop), moves));
			Assert::IsTrue(moveListContains(Move(D4, G7, Bishop), moves));
			Assert::IsTrue(moveListContains(Move(D4, H8, Bishop), moves));

			Assert::IsTrue(moveListContains(Move(D4, E3, Bishop), moves));
			Assert::IsTrue(moveListContains(Move(D4, F2, Bishop), moves));
			Assert::IsTrue(moveListContains(Move(D4, G1, Bishop), moves));
		}
		TEST_METHOD(generatingQueenMoves)
		{
			ChessBoardTest board("8/8/6p1/6P1/8/1n2Q3/8/8 w - - 0 1");
			
			MoveList moves = board.getPseudoLegalMoves();
			Assert::AreEqual(22, (int)moves.size());
			
			Assert::IsTrue(moveListContains(Move(E3, E4, Queen), moves));
			Assert::IsTrue(moveListContains(Move(E3, E5, Queen), moves));
			Assert::IsTrue(moveListContains(Move(E3, E6, Queen), moves));
			Assert::IsTrue(moveListContains(Move(E3, E7, Queen), moves));
			Assert::IsTrue(moveListContains(Move(E3, E8, Queen), moves));

			Assert::IsTrue(moveListContains(Move(E3, F4, Queen), moves));
			
			Assert::IsTrue(moveListContains(Move(E3, F3, Queen), moves));
			Assert::IsTrue(moveListContains(Move(E3, G3, Queen), moves));
			Assert::IsTrue(moveListContains(Move(E3, H3, Queen), moves));

			Assert::IsTrue(moveListContains(Move(E3, F2, Queen), moves));
			Assert::IsTrue(moveListContains(Move(E3, G1, Queen), moves));

			Assert::IsTrue(moveListContains(Move(E3, E2, Queen), moves));
			Assert::IsTrue(moveListContains(Move(E3, E1, Queen), moves));
			
			Assert::IsTrue(moveListContains(Move(E3, D2, Queen), moves));
			Assert::IsTrue(moveListContains(Move(E3, C1, Queen), moves));

			Assert::IsTrue(moveListContains(Move(E3, D3, Queen), moves));
			Assert::IsTrue(moveListContains(Move(E3, C3, Queen), moves));

			Assert::IsTrue(moveListContains(Move(E3, D4, Queen), moves));
			Assert::IsTrue(moveListContains(Move(E3, C5, Queen), moves));
			Assert::IsTrue(moveListContains(Move(E3, B6, Queen), moves));
			Assert::IsTrue(moveListContains(Move(E3, A7, Queen), moves));
		}
	};
}