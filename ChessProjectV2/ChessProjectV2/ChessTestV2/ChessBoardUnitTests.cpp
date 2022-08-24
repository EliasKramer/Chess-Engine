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

		TEST_METHOD(setupBoardTest)
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
		TEST_METHOD(startingPositionTest)
		{
			Assert::IsTrue(STARTING_FEN == "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		}
		TEST_METHOD(positionIsValidTest)
		{
			ChessBoardTest board;

			//new position is too far left
			Assert::IsFalse(board.destinationIsOnBoard(A3, WEST));
			Assert::IsFalse(board.destinationIsOnBoard(A3, NORTH_WEST));
			Assert::IsFalse(board.destinationIsOnBoard(A3, SOUTH_WEST));

			Assert::IsTrue(board.destinationIsOnBoard(A3, EAST));
			Assert::IsTrue(board.destinationIsOnBoard(A3, NORTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(A3, SOUTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(A3, SOUTH));
			Assert::IsTrue(board.destinationIsOnBoard(A3, NORTH));

			//new position is too far right
			Assert::IsFalse(board.destinationIsOnBoard(H3, EAST));
			Assert::IsFalse(board.destinationIsOnBoard(H3, NORTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(H3, SOUTH_EAST));

			Assert::IsTrue(board.destinationIsOnBoard(H3, WEST));
			Assert::IsTrue(board.destinationIsOnBoard(H3, NORTH_WEST));
			Assert::IsTrue(board.destinationIsOnBoard(H3, SOUTH_WEST));
			Assert::IsTrue(board.destinationIsOnBoard(H3, SOUTH));
			Assert::IsTrue(board.destinationIsOnBoard(H3, NORTH));

			//new position is too far up
			Assert::IsFalse(board.destinationIsOnBoard(E8, NORTH));
			Assert::IsFalse(board.destinationIsOnBoard(E8, NORTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(E8, NORTH_WEST));

			Assert::IsTrue(board.destinationIsOnBoard(E8, SOUTH));
			Assert::IsTrue(board.destinationIsOnBoard(E8, SOUTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(E8, SOUTH_WEST));
			Assert::IsTrue(board.destinationIsOnBoard(E8, EAST));
			Assert::IsTrue(board.destinationIsOnBoard(E8, WEST));

			//new position is too far down
			Assert::IsFalse(board.destinationIsOnBoard(E1, SOUTH));
			Assert::IsFalse(board.destinationIsOnBoard(E1, SOUTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(E1, SOUTH_WEST));

			Assert::IsTrue(board.destinationIsOnBoard(E1, NORTH));
			Assert::IsTrue(board.destinationIsOnBoard(E1, NORTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(E1, NORTH_WEST));
			Assert::IsTrue(board.destinationIsOnBoard(E1, EAST));
			Assert::IsTrue(board.destinationIsOnBoard(E1, WEST));

			//knights move is too far left
			Assert::IsFalse(board.destinationIsOnBoard(B3, WEST_NORTH_WEST));
			Assert::IsFalse(board.destinationIsOnBoard(B3, WEST_SOUTH_WEST));

			Assert::IsTrue(board.destinationIsOnBoard(B3, SOUTH_SOUTH_WEST));
			Assert::IsTrue(board.destinationIsOnBoard(B3, NORTH_NORTH_WEST));

			//knights move is too far right
			Assert::IsFalse(board.destinationIsOnBoard(G3, EAST_NORTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(G3, EAST_SOUTH_EAST));

			Assert::IsTrue(board.destinationIsOnBoard(G3, SOUTH_SOUTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(G3, NORTH_NORTH_EAST));

			//left lower corner
			Assert::IsTrue(board.destinationIsOnBoard(A1, NORTH));
			Assert::IsTrue(board.destinationIsOnBoard(A1, NORTH_NORTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(A1, NORTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(A1, EAST_NORTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(A1, EAST));

			Assert::IsFalse(board.destinationIsOnBoard(A1, EAST_SOUTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(A1, SOUTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(A1, SOUTH_SOUTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(A1, SOUTH));
			Assert::IsFalse(board.destinationIsOnBoard(A1, SOUTH_SOUTH_WEST));
			Assert::IsFalse(board.destinationIsOnBoard(A1, SOUTH_WEST));
			Assert::IsFalse(board.destinationIsOnBoard(A1, WEST_SOUTH_WEST));
			Assert::IsFalse(board.destinationIsOnBoard(A1, WEST));
			Assert::IsFalse(board.destinationIsOnBoard(A1, WEST_NORTH_WEST));
			Assert::IsFalse(board.destinationIsOnBoard(A1, NORTH_WEST));
			Assert::IsFalse(board.destinationIsOnBoard(A1, NORTH_NORTH_WEST));

			//right lower corner
			Assert::IsTrue(board.destinationIsOnBoard(H1, NORTH));

			Assert::IsFalse(board.destinationIsOnBoard(H1, NORTH_NORTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(H1, NORTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(H1, EAST_NORTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(H1, EAST));
			Assert::IsFalse(board.destinationIsOnBoard(H1, EAST_SOUTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(H1, SOUTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(H1, SOUTH_SOUTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(H1, SOUTH));
			Assert::IsFalse(board.destinationIsOnBoard(H1, SOUTH_SOUTH_WEST));
			Assert::IsFalse(board.destinationIsOnBoard(H1, SOUTH_WEST));
			Assert::IsFalse(board.destinationIsOnBoard(H1, WEST_SOUTH_WEST));

			Assert::IsTrue(board.destinationIsOnBoard(H1, WEST));
			Assert::IsTrue(board.destinationIsOnBoard(H1, WEST_NORTH_WEST));
			Assert::IsTrue(board.destinationIsOnBoard(H1, NORTH_WEST));
			Assert::IsTrue(board.destinationIsOnBoard(H1, NORTH_NORTH_WEST));

			//left upper corner
			Assert::IsFalse(board.destinationIsOnBoard(A8, NORTH));
			Assert::IsFalse(board.destinationIsOnBoard(A8, NORTH_NORTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(A8, NORTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(A8, EAST_NORTH_EAST));

			Assert::IsTrue(board.destinationIsOnBoard(A8, EAST));
			Assert::IsTrue(board.destinationIsOnBoard(A8, EAST_SOUTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(A8, SOUTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(A8, SOUTH_SOUTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(A8, SOUTH));

			Assert::IsFalse(board.destinationIsOnBoard(A8, SOUTH_SOUTH_WEST));
			Assert::IsFalse(board.destinationIsOnBoard(A8, SOUTH_WEST));
			Assert::IsFalse(board.destinationIsOnBoard(A8, WEST_SOUTH_WEST));
			Assert::IsFalse(board.destinationIsOnBoard(A8, WEST));
			Assert::IsFalse(board.destinationIsOnBoard(A8, WEST_NORTH_WEST));
			Assert::IsFalse(board.destinationIsOnBoard(A8, NORTH_WEST));
			Assert::IsFalse(board.destinationIsOnBoard(A8, NORTH_NORTH_WEST));

			//right upper corner
			Assert::IsFalse(board.destinationIsOnBoard(H8, NORTH));
			Assert::IsFalse(board.destinationIsOnBoard(H8, NORTH_NORTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(H8, NORTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(H8, EAST_NORTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(H8, EAST));
			Assert::IsFalse(board.destinationIsOnBoard(H8, EAST_SOUTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(H8, SOUTH_EAST));
			Assert::IsFalse(board.destinationIsOnBoard(H8, SOUTH_SOUTH_EAST));

			Assert::IsTrue(board.destinationIsOnBoard(H8, SOUTH));
			Assert::IsTrue(board.destinationIsOnBoard(H8, SOUTH_SOUTH_WEST));
			Assert::IsTrue(board.destinationIsOnBoard(H8, SOUTH_WEST));
			Assert::IsTrue(board.destinationIsOnBoard(H8, WEST_SOUTH_WEST));
			Assert::IsTrue(board.destinationIsOnBoard(H8, WEST));

			Assert::IsFalse(board.destinationIsOnBoard(H8, WEST_NORTH_WEST));
			Assert::IsFalse(board.destinationIsOnBoard(H8, NORTH_WEST));
			Assert::IsFalse(board.destinationIsOnBoard(H8, NORTH_NORTH_WEST));

			//B2
			Assert::IsTrue(board.destinationIsOnBoard(B2, NORTH));
			Assert::IsTrue(board.destinationIsOnBoard(B2, NORTH_NORTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(B2, NORTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(B2, EAST_NORTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(B2, EAST));
			Assert::IsTrue(board.destinationIsOnBoard(B2, EAST_SOUTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(B2, SOUTH_EAST));

			Assert::IsFalse(board.destinationIsOnBoard(B2, SOUTH_SOUTH_EAST));

			Assert::IsTrue(board.destinationIsOnBoard(B2, SOUTH));

			Assert::IsFalse(board.destinationIsOnBoard(B2, SOUTH_SOUTH_WEST));

			Assert::IsTrue(board.destinationIsOnBoard(B2, SOUTH_WEST));

			Assert::IsFalse(board.destinationIsOnBoard(B2, WEST_SOUTH_WEST));

			Assert::IsTrue(board.destinationIsOnBoard(B2, WEST));

			Assert::IsFalse(board.destinationIsOnBoard(B2, WEST_NORTH_WEST));

			Assert::IsTrue(board.destinationIsOnBoard(B2, NORTH_WEST));

			//G2
			Assert::IsTrue(board.destinationIsOnBoard(G2, NORTH));
			Assert::IsTrue(board.destinationIsOnBoard(G2, NORTH_NORTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(G2, NORTH_EAST));

			Assert::IsFalse(board.destinationIsOnBoard(G2, EAST_NORTH_EAST));

			Assert::IsTrue(board.destinationIsOnBoard(G2, EAST));
			
			Assert::IsFalse(board.destinationIsOnBoard(G2, EAST_SOUTH_EAST));
			
			Assert::IsTrue(board.destinationIsOnBoard(G2, SOUTH_EAST));
			
			Assert::IsFalse(board.destinationIsOnBoard(G2, SOUTH_SOUTH_EAST));

			Assert::IsTrue(board.destinationIsOnBoard(G2, SOUTH));

			Assert::IsFalse(board.destinationIsOnBoard(G2, SOUTH_SOUTH_WEST));

			Assert::IsTrue(board.destinationIsOnBoard(G2, SOUTH_WEST));
			Assert::IsTrue(board.destinationIsOnBoard(G2, WEST_SOUTH_WEST));
			Assert::IsTrue(board.destinationIsOnBoard(G2, WEST));
			Assert::IsTrue(board.destinationIsOnBoard(G2, WEST_NORTH_WEST));
			Assert::IsTrue(board.destinationIsOnBoard(G2, NORTH_WEST));
			Assert::IsTrue(board.destinationIsOnBoard(G2, NORTH_NORTH_WEST));

			//B7
			Assert::IsTrue(board.destinationIsOnBoard(B7, NORTH));
			
			Assert::IsFalse(board.destinationIsOnBoard(B7, NORTH_NORTH_EAST));

			Assert::IsTrue(board.destinationIsOnBoard(B7, NORTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(B7, EAST_NORTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(B7, EAST));
			Assert::IsTrue(board.destinationIsOnBoard(B7, EAST_SOUTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(B7, SOUTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(B7, SOUTH_SOUTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(B7, SOUTH));
			Assert::IsTrue(board.destinationIsOnBoard(B7, SOUTH_SOUTH_WEST));
			Assert::IsTrue(board.destinationIsOnBoard(B7, SOUTH_WEST));
			
			Assert::IsFalse(board.destinationIsOnBoard(B7, WEST_SOUTH_WEST));

			Assert::IsTrue(board.destinationIsOnBoard(B7, WEST));

			Assert::IsFalse(board.destinationIsOnBoard(B7, WEST_NORTH_WEST));

			Assert::IsTrue(board.destinationIsOnBoard(B7, NORTH_WEST));
			
			Assert::IsFalse(board.destinationIsOnBoard(B7, NORTH_NORTH_WEST));

			//G7
			Assert::IsTrue(board.destinationIsOnBoard(G7, NORTH));
			
			Assert::IsFalse(board.destinationIsOnBoard(G7, NORTH_NORTH_EAST));
			
			Assert::IsTrue(board.destinationIsOnBoard(G7, NORTH_EAST));
			
			Assert::IsFalse(board.destinationIsOnBoard(G7, EAST_NORTH_EAST));
			
			Assert::IsTrue(board.destinationIsOnBoard(G7, EAST));

			Assert::IsFalse(board.destinationIsOnBoard(G7, EAST_SOUTH_EAST));

			Assert::IsTrue(board.destinationIsOnBoard(G7, SOUTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(G7, SOUTH_SOUTH_EAST));
			Assert::IsTrue(board.destinationIsOnBoard(G7, SOUTH));
			Assert::IsTrue(board.destinationIsOnBoard(G7, SOUTH_SOUTH_WEST));
			Assert::IsTrue(board.destinationIsOnBoard(G7, SOUTH_WEST));
			Assert::IsTrue(board.destinationIsOnBoard(G7, WEST_SOUTH_WEST));
			Assert::IsTrue(board.destinationIsOnBoard(G7, WEST));
			Assert::IsTrue(board.destinationIsOnBoard(G7, WEST_NORTH_WEST));
			Assert::IsTrue(board.destinationIsOnBoard(G7, NORTH_WEST));
			
			Assert::IsFalse(board.destinationIsOnBoard(G7, NORTH_NORTH_WEST));
		}
	};
}