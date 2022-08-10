#include "CppUnitTest.h"
#include "../ChessProjectV2/BitBoard.h"
#include "../ChessProjectV2/ChessBoard.h"
#include "../ChessProjectV2/DataAndTypes.h"
#include "../ChessProjectV2/ChessBoardTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessBoardUnitTest
{
	TEST_CLASS(ChessBoardUnitTest)
	{
	public:

		TEST_METHOD(setupBoard)
		{
			ChessBoardTest board;

			Assert::AreEqual(BITBOARD_NONE, board.getAllPieces());
			Assert::AreEqual(BITBOARD_NONE, board.getAllPiecesOfColor(ChessColor::White));
			Assert::AreEqual(BITBOARD_NONE, board.getAllPiecesOfColor(ChessColor::Black));
			Assert::AreEqual(BITBOARD_NONE, board.getAllPiecesOfType(Pawn));
			Assert::AreEqual(BITBOARD_NONE, board.getAllPiecesOfType(Bishop));
			Assert::AreEqual(BITBOARD_NONE, board.getAllPiecesOfType(Knight));
			Assert::AreEqual(BITBOARD_NONE, board.getAllPiecesOfType(Rook));
			Assert::AreEqual(BITBOARD_NONE, board.getAllPiecesOfType(Queen));
			Assert::AreEqual(BITBOARD_NONE, board.getAllPiecesOfType(King));

			board.setupBoard();

			Assert::AreEqual(RANK_1 & RANK_2 & RANK_7 & RANK_8, board.getAllPieces());
			
			Assert::AreEqual(RANK_1 & RANK_2, board.getAllPiecesOfColor(ChessColor::White));
			Assert::AreEqual(RANK_7 & RANK_8, board.getAllPiecesOfColor(ChessColor::Black));

			Assert::AreEqual(RANK_2 & RANK_7, board.getAllPiecesOfType(Pawn));
			
			Assert::AreEqual(
				BB_SQUARE[C1] & BB_SQUARE[F1] & BB_SQUARE[C8] & BB_SQUARE[F8],
				board.getAllPiecesOfType(Bishop));
			Assert::AreEqual(
				BB_SQUARE[B1] & BB_SQUARE[G1] & BB_SQUARE[B8] & BB_SQUARE[G8],
				board.getAllPiecesOfType(Knight));
			Assert::AreEqual(
				BB_SQUARE[A1] & BB_SQUARE[H1] & BB_SQUARE[A8] & BB_SQUARE[H8],
				board.getAllPiecesOfType(Rook));
			Assert::AreEqual(
				BB_SQUARE[D1] & BB_SQUARE[D8],
				board.getAllPiecesOfType(Queen));
			Assert::AreEqual(
				BB_SQUARE[E1] & BB_SQUARE[E8],
				board.getAllPiecesOfType(King));
			
			Assert::AreEqual(
				BB_SQUARE[A1] & BB_SQUARE[E1] & BB_SQUARE[H1] &
				BB_SQUARE[A8] & BB_SQUARE[E8] & BB_SQUARE[H8],
				board.getAllAvailableCastleMoves());
		}
		TEST_METHOD(fenNotation)
		{
			ChessBoardTest boardFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			ChessBoardTest boardNormal;
			boardNormal.setupBoard();

			
		}
	};
}