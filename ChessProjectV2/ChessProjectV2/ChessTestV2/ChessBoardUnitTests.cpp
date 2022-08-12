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

			Assert::IsFalse(board.casltingAllowed(White, CastleLong));
			Assert::IsFalse(board.casltingAllowed(White, CastleShort));
			Assert::IsFalse(board.casltingAllowed(Black, CastleLong));
			Assert::IsFalse(board.casltingAllowed(Black, CastleShort));

			Assert::IsTrue(White == board.getTurnColor());

			Assert::IsTrue(SQUARE_NONE == board.getEnPassantSquare());

			Assert::IsTrue(0 == board.getHalfMoveClock());

			Assert::IsTrue(1 == board.getMoveNumber());
			
			board.setupBoard();

			Assert::AreEqual(RANK_1 | RANK_2 | RANK_7 | RANK_8, board.getAllPieces());
			
			Assert::AreEqual(RANK_1 | RANK_2, board.getAllPiecesOfColor(ChessColor::White));
			Assert::AreEqual(RANK_7 | RANK_8, board.getAllPiecesOfColor(ChessColor::Black));

			Assert::AreEqual(RANK_2 | RANK_7, board.getAllPiecesOfType(Pawn));
			
			Assert::AreEqual(
				BB_SQUARE[C1] | BB_SQUARE[F1] | BB_SQUARE[C8] | BB_SQUARE[F8],
				board.getAllPiecesOfType(Bishop));
			Assert::AreEqual(
				BB_SQUARE[B1] | BB_SQUARE[G1] | BB_SQUARE[B8] | BB_SQUARE[G8],
				board.getAllPiecesOfType(Knight));
			Assert::AreEqual(
				BB_SQUARE[A1] | BB_SQUARE[H1] | BB_SQUARE[A8] | BB_SQUARE[H8],
				board.getAllPiecesOfType(Rook));
			Assert::AreEqual(
				BB_SQUARE[D1] | BB_SQUARE[D8],
				board.getAllPiecesOfType(Queen));
			Assert::AreEqual(
				BB_SQUARE[E1] | BB_SQUARE[E8],
				board.getAllPiecesOfType(King));
			
			Assert::IsTrue(board.casltingAllowed(White, CastleLong));
			Assert::IsTrue(board.casltingAllowed(White, CastleShort));
			Assert::IsTrue(board.casltingAllowed(Black, CastleLong));
			Assert::IsTrue(board.casltingAllowed(Black, CastleShort));
		
			Assert::IsTrue(White == board.getTurnColor());

			Assert::IsTrue(SQUARE_NONE == board.getEnPassantSquare());

			Assert::IsTrue(0 == board.getHalfMoveClock());

			Assert::IsTrue(1 == board.getMoveNumber());
		}
		TEST_METHOD(fenNotationSetup)
		{
			ChessBoardTest boardFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			ChessBoardTest boardNormal;
			boardNormal.setupBoard();

			Assert::AreEqual(0xffff00000000ffffULL, boardFen.getAllPieces());
			Assert::AreEqual(0xffff00000000ffffULL, boardNormal.getAllPieces());
			Assert::AreEqual(boardNormal.getAllPieces(), boardFen.getAllPieces());

			Assert::AreEqual(0xffff000000000000ULL, boardFen.getAllPiecesOfColor(Black));
			Assert::AreEqual(0xffff000000000000ULL, boardNormal.getAllPiecesOfColor(Black));
			Assert::AreEqual(boardNormal.getAllPiecesOfColor(Black), boardFen.getAllPiecesOfColor(Black));

			Assert::AreEqual(0x000000000000ffffULL, boardFen.getAllPiecesOfColor(White));
			Assert::AreEqual(0x000000000000ffffULL, boardNormal.getAllPiecesOfColor(White));
			Assert::AreEqual(boardNormal.getAllPiecesOfColor(White), boardFen.getAllPiecesOfColor(White));

			Assert::AreEqual(0xff00000000ff00ULL, boardFen.getAllPiecesOfType(Pawn));
			Assert::AreEqual(0xff00000000ff00ULL, boardNormal.getAllPiecesOfType(Pawn));
			Assert::AreEqual(boardNormal.getAllPiecesOfType(Pawn), boardFen.getAllPiecesOfType(Pawn));
			
			Assert::AreEqual(0x4200000000000042ULL, boardFen.getAllPiecesOfType(Knight));
			Assert::AreEqual(0x4200000000000042ULL, boardNormal.getAllPiecesOfType(Knight));
			Assert::AreEqual(boardNormal.getAllPiecesOfType(Knight), boardFen.getAllPiecesOfType(Knight));

			Assert::AreEqual(0x2400000000000024ULL, boardFen.getAllPiecesOfType(Bishop));
			Assert::AreEqual(0x2400000000000024ULL, boardNormal.getAllPiecesOfType(Bishop));
			Assert::AreEqual(boardNormal.getAllPiecesOfType(Bishop), boardFen.getAllPiecesOfType(Bishop));

			Assert::AreEqual(0x8100000000000081ULL, boardFen.getAllPiecesOfType(Rook));
			Assert::AreEqual(0x8100000000000081ULL, boardNormal.getAllPiecesOfType(Rook));
			Assert::AreEqual(boardNormal.getAllPiecesOfType(Rook), boardFen.getAllPiecesOfType(Rook));

			Assert::AreEqual(0x800000000000008ULL, boardFen.getAllPiecesOfType(Queen));
			Assert::AreEqual(0x800000000000008ULL, boardNormal.getAllPiecesOfType(Queen));
			Assert::AreEqual(boardNormal.getAllPiecesOfType(Queen), boardFen.getAllPiecesOfType(Queen));
				
			Assert::AreEqual(0x1000000000000010ULL, boardFen.getAllPiecesOfType(King));
			Assert::AreEqual(0x1000000000000010ULL, boardNormal.getAllPiecesOfType(King));
			Assert::AreEqual(boardNormal.getAllPiecesOfType(King), boardFen.getAllPiecesOfType(King));
			
			Assert::IsTrue(White == boardFen.getTurnColor());
			Assert::IsTrue(White == boardNormal.getTurnColor());

			Assert::IsTrue(boardNormal.casltingAllowed(White, CastleLong));
			Assert::IsTrue(boardNormal.casltingAllowed(White, CastleShort));
			Assert::IsTrue(boardNormal.casltingAllowed(Black, CastleLong));
			Assert::IsTrue(boardNormal.casltingAllowed(Black, CastleShort));
			Assert::IsTrue(boardFen.casltingAllowed(White, CastleLong));
			Assert::IsTrue(boardFen.casltingAllowed(White, CastleShort));
			Assert::IsTrue(boardFen.casltingAllowed(Black, CastleLong));
			Assert::IsTrue(boardFen.casltingAllowed(Black, CastleShort));

			Assert::IsTrue(SQUARE_NONE == boardNormal.getEnPassantSquare());
			Assert::IsTrue(SQUARE_NONE == boardFen.getEnPassantSquare());

			Assert::IsTrue(0 == boardNormal.getHalfMoveClock());
			Assert::IsTrue(0 == boardFen.getHalfMoveClock());

			Assert::IsTrue(1 == boardNormal.getMoveNumber());
			Assert::IsTrue(1 == boardFen.getMoveNumber());
		}
		TEST_METHOD(fenNotationTests)
		{
			ChessBoardTest board("8/8/8/8/8/8/8/8 w KQkq e3 0 1");
			Assert::IsTrue(E3 == board.getEnPassantSquare());

			board = ChessBoardTest("8/8/8/8/8/8/8/8 w KQkq h6 0 1");
			Assert::IsTrue(H6 == board.getEnPassantSquare());

			board = ChessBoardTest("8/8/8/8/8/8/8/8 w Kq - 0 1");
			Assert::IsTrue(board.casltingAllowed(White, CastleShort));
			Assert::IsTrue(board.casltingAllowed(Black, CastleLong));
			Assert::IsFalse(board.casltingAllowed(White, CastleLong));
			Assert::IsFalse(board.casltingAllowed(Black, CastleShort));

			board = ChessBoardTest("8/8/8/8/8/8/8/8 b KQkq - 0 1");
			Assert::IsTrue(Black == board.getTurnColor());

			board = ChessBoardTest("8/8/8/8/8/8/8/8 w KQkq - 99 1");
			Assert::IsTrue(99 == board.getHalfMoveClock());

			board = ChessBoardTest("8/8/8/8/8/8/8/8 w KQkq - 0 99");
			Assert::IsTrue(99 == board.getMoveNumber());

			board = ChessBoardTest("8/7p/8/8/8/8/8/3B w KQkq - 0 1");
			Assert::IsTrue(BB_SQUARE[H7] == board.getAllPiecesOfType(Pawn));
			Assert::IsTrue(BB_SQUARE[H7] == board.getAllPiecesOfColor(Black));
			Assert::IsTrue(BB_SQUARE[D1] == board.getAllPiecesOfType(Bishop));
			Assert::IsTrue(BB_SQUARE[D1] == board.getAllPiecesOfColor(White));
		}
	};
}