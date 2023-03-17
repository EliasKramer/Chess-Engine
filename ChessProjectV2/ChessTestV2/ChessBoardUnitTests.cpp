#include "CppUnitTest.h"
#include "../ChessProjectV2/BitBoard.h"
#include "../ChessProjectV2/ChessBoard.h"
#include "../ChessProjectV2/DataAndTypes.h"
#include "../ChessProjectV2/ChessBoardTest.h"
#include "../ChessProjectV2/Move.h"
#include "../ChessProjectV2/MoveEnPassant.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessBoardUnitTest
{
	TEST_CLASS(ChessBoardUnitTest)
	{
	public:
		TEST_METHOD(fenNotationSetup)
		{
			ChessBoardTest boardFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

			Assert::AreEqual(0xffff00000000ffffULL, boardFen.getAllPieces());

			Assert::AreEqual(0xffff000000000000ULL, boardFen.getAllPiecesOfColor(Black));

			Assert::AreEqual(0x000000000000ffffULL, boardFen.getAllPiecesOfColor(White));

			Assert::AreEqual(0xff00000000ff00ULL, boardFen.getAllPiecesOfType(Pawn));

			Assert::AreEqual(0x4200000000000042ULL, boardFen.getAllPiecesOfType(Knight));

			Assert::AreEqual(0x2400000000000024ULL, boardFen.getAllPiecesOfType(Bishop));

			Assert::AreEqual(0x8100000000000081ULL, boardFen.getAllPiecesOfType(Rook));

			Assert::AreEqual(0x800000000000008ULL, boardFen.getAllPiecesOfType(Queen));

			Assert::AreEqual(0x1000000000000010ULL, boardFen.getAllPiecesOfType(King));

			Assert::IsTrue(White == boardFen.getTurnColor());

			Assert::IsTrue(boardFen.casltingAllowed(White, CastleLong));
			Assert::IsTrue(boardFen.casltingAllowed(White, CastleShort));
			Assert::IsTrue(boardFen.casltingAllowed(Black, CastleLong));
			Assert::IsTrue(boardFen.casltingAllowed(Black, CastleShort));

			Assert::IsTrue(SQUARE_NONE == boardFen.getEnPassantSquare());

			Assert::IsTrue(0 == boardFen.getHalfMoveClock());

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
		TEST_METHOD(fieldIsUnderattackByPawn)
		{
			ChessBoardTest board("8/8/8/8/2p5/3K4/8/8 w - - 0 1");
			Assert::IsTrue(board.fieldIsUnderAttack(D3));
			
			board = ChessBoardTest("8/8/8/8/4p3/3K4/8/8 w - - 0 1");
			Assert::IsTrue(board.fieldIsUnderAttack(D3));

			board = ChessBoardTest("8/8/8/8/2p1p3/3K4/8/8 w - - 0 1");
			Assert::IsTrue(board.fieldIsUnderAttack(D3));

			board = ChessBoardTest("8/8/8/8/2K5/3p4/8/8 w - - 0 1");
			Assert::IsFalse(board.fieldIsUnderAttack(D3));

			board = ChessBoardTest("8/8/8/8/8/3k4/3P4/8 b - - 0 1");
			Assert::IsFalse(board.fieldIsUnderAttack(D3));
		}
		TEST_METHOD(fieldIsUnderattackByKnight)
		{
			ChessBoardTest board("8/8/8/3k4/8/4N3/8/8 b - - 0 1");
			Assert::IsTrue(board.fieldIsUnderAttack(D5));
			
			board = ChessBoardTest("8/8/5N2/3k4/5N2/4N3/8/8 b - - 0 1");
			Assert::IsTrue(board.fieldIsUnderAttack(D5));

			board = ChessBoardTest("8/8/8/8/8/4n3/6K1/8 w - - 0 1");
			Assert::IsTrue(board.fieldIsUnderAttack(G2));

			board = ChessBoardTest("8/8/8/8/8/4n1K1/8/8 w - - 0 1");
			Assert::IsFalse(board.fieldIsUnderAttack(G3));

			board = ChessBoardTest("8/8/8/8/8/4nK2/8/8 w - - 0 1");
			Assert::IsFalse(board.fieldIsUnderAttack(F3));
		}
		//started to only test legal positions here (with both kings)
		TEST_METHOD(fieldIsUnderAttackByKing)
		{
			ChessBoardTest board("8/1K6/8/8/4k3/5P2/8/8 w  - - 0 1");
			Assert::IsTrue(board.fieldIsUnderAttack(F5));

			board = ChessBoardTest("8/8/8/3k4/4N3/8/8/7K w - - 0 1");
			Assert::IsTrue(board.fieldIsUnderAttack(E5));

			board = ChessBoardTest("8/8/8/3k4/8/2N5/8/7K w - - 0 1");
			Assert::IsFalse(board.fieldIsUnderAttack(C3));

			board = ChessBoardTest("8/8/6k1/1Kp5/8/8/8/8 b - - 0 1");
			Assert::IsTrue(board.fieldIsUnderAttack(C5));

			board = ChessBoardTest("K7/p7/6k1/8/8/8/8/8 b - - 0 1");
			Assert::IsTrue(board.fieldIsUnderAttack(A7));

			board = ChessBoardTest("K7/8/p5k1/8/8/8/8/8 b - - 0 1");
			Assert::IsFalse(board.fieldIsUnderAttack(A6));
		}
		TEST_METHOD(fieldGetsAttackedBySlidingPiece)
		{
			//gets attacked by bishop
			ChessBoardTest board("7k/8/8/8/3N4/8/8/K5b1 w - - 0 1");
			Assert::IsTrue(board.fieldIsUnderAttack(D4));

			//gets not attacked. bishop blocks bishop
			board = ChessBoardTest("7k/8/8/8/3N4/8/5B2/K5b1 w - - 0 1");
			Assert::IsFalse(board.fieldIsUnderAttack(D4));

			//rook attacks rook
			board = ChessBoardTest("3R3k/8/8/8/3r4/8/8/K7 b - - 0 1");
			Assert::IsTrue(board.fieldIsUnderAttack(D4));

			//gets not attacked. queen blocks
			board = ChessBoardTest("3R3k/8/3q4/8/3r4/8/8/K7 b - - 0 1");
			Assert::IsFalse(board.fieldIsUnderAttack(D4));

			//Queen also attacks blocking queen
			board = ChessBoardTest("1Q1R3k/8/3q4/8/3r4/8/8/K7 b - - 0 1");
			Assert::IsTrue(board.fieldIsUnderAttack(D6));
			Assert::IsFalse(board.fieldIsUnderAttack(D4));
		}
		TEST_METHOD(isUnderAttackAfterMove)
		{
			//move knight - king is under attack after that
			ChessBoardTest board("7k/8/8/8/8/8/8/K1N1r3 w - - 0 1");
			Move m(C1, B3);
			Assert::IsTrue(board.fieldIsUnderAttackWithMoveBB(A1, m.getBBWithMoveDone()));

			//pawn takes en passant - king is under attack
			board = ChessBoardTest("7k/8/8/KPp3q1/8/8/8/8 w - c6 0 1");
			MoveEnPassant me(B5, C6, C5);
			Assert::IsTrue(board.fieldIsUnderAttackWithMoveBB(A5, me.getBBWithMoveDone()));

			//pawn takes attacking knight - king is not under attack
			board = ChessBoardTest("7k/8/2n5/KP6/8/8/8/8 w - - 0 1");
			Move m2(B5, C6);
			Assert::IsFalse(board.fieldIsUnderAttackWithMoveBB(A5, m2.getBBWithMoveDone()));

			//rook takes attacking pawn - king is not under attack
			board = ChessBoardTest("7k/8/1p6/KR6/8/8/8/8 w - - 0 1");
			Move m3(B5, B6);
			Assert::IsFalse(board.fieldIsUnderAttackWithMoveBB(A5, m3.getBBWithMoveDone()));

			//black bishop takes attacking queen - king is not under attack
			board = ChessBoardTest("8/4b3/3Q2k1/K7/8/8/8/8 b - - 0 1");
			Move m4(E7, D6);
			Assert::IsFalse(board.fieldIsUnderAttackWithMoveBB(G6, m4.getBBWithMoveDone()));	
		}
		TEST_METHOD(legalMovesCheck)
		{
			//not matter what castle move, it will be always legal,
			//because it has been checked for legality before
			ChessBoardTest board(EMPTY_FEN);
			Assert::IsTrue(board.isLegal(std::make_unique<MoveCastle>(White, CastleLong)));
		}
		TEST_METHOD(equalCheck)
		{
			ChessBoardTest board1("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			ChessBoardTest board2(STARTING_FEN);
			Assert::IsTrue(board1 == board2);
			Assert::IsFalse(board1 != board2);

			//castling not the same
			board1 = ChessBoardTest("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			board2 = ChessBoardTest("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w Qkq - 0 1");

			Assert::IsFalse(board1 == board2);
			Assert::IsTrue(board1 != board2);

			//move color not the same
			board1 = ChessBoardTest("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			board2 = ChessBoardTest("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1");

			Assert::IsFalse(board1 == board2);
			Assert::IsTrue(board1 != board2);
			
			//en passant not the same
			board1 = ChessBoardTest("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			board2 = ChessBoardTest("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq e4 0 1");

			Assert::IsFalse(board1 == board2);
			Assert::IsTrue(board1 != board2);
			
			//half move clock not the same
			board1 = ChessBoardTest("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			board2 = ChessBoardTest("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 1 1");

			Assert::IsFalse(board1 == board2);
			Assert::IsTrue(board1 != board2);
			
			//moves not the same
			board1 = ChessBoardTest("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			board2 = ChessBoardTest("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 2");

			Assert::IsFalse(board1 == board2);
			Assert::IsTrue(board1 != board2);

			//color of piece not the same
			board1 = ChessBoardTest("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			board2 = ChessBoardTest("Rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

			Assert::IsFalse(board1 == board2);
			Assert::IsTrue(board1 != board2);

			//no piece at all at one pos
			board1 = ChessBoardTest("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			board2 = ChessBoardTest("1nbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

			Assert::IsFalse(board1 == board2);
			Assert::IsTrue(board1 != board2);
		}
		TEST_METHOD(copyBoardTest)
		{
			ChessBoard board1(STARTING_FEN);
			ChessBoard board2 = board1.getCopyByValue();
			Assert::IsTrue(board1 == board2);

			board1 = ChessBoard("r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1");
			board2 = board1.getCopyByValue();
			Assert::IsTrue(board1 == board2);
		}
	};
}