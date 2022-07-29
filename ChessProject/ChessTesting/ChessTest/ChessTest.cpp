#include "pch.h"
#include "CppUnitTest.h"
#include <list>
#include <iostream>
#include "../../ChessProject/MetaData.h"
#include "../../ChessProject/ChessPiece.h"
#include "../../ChessProject/ChessBoard.h"
#include "../../ChessProject/ChessBoardTest.h"
#include "../../ChessProject/Move.h"
#include "../../ChessProject/Coordinate.h"
#include "../../ChessProject/RayCastOptions.h"
#include "../../ChessProject/RayCastResult.h"
#include "TestMethods.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessTest
{
	TEST_CLASS(ChessTest)
	{
	public:
		TEST_METHOD(ColorTest)
		{
			ChessColor black = ChessColor::Black;
			ChessColor white = ChessColor::White;
			Assert::AreEqual((int)ChessColor::Black, (int)black);
			Assert::AreEqual((int)ChessColor::White, (int)white);
			Assert::AreNotEqual((int)black, (int)white);
		}
		TEST_METHOD(StringColorTest)
		{
			std::string b = "B";
			std::string w = "W";
			Assert::AreNotEqual(b, w);

			std::string blackString = "Black";
			std::string whiteString = "White";

			Assert::AreNotEqual(blackString, whiteString);

			ChessColor white = ChessColor::White;
			ChessColor black = ChessColor::Black;

			std::string shortWhite = getShortNameOfChessColor(&white);
			Assert::AreEqual(w, shortWhite);
			std::string shortBlack = getShortNameOfChessColor(&black);
			Assert::AreEqual(b, shortBlack);

			std::string longWhite = getLongNameOfChessColor(&white);
			Assert::AreEqual(whiteString, longWhite);
			std::string longBlack = getLongNameOfChessColor(&black);
			Assert::AreEqual(blackString, longBlack);

			Assert::AreNotEqual(getLongNameOfChessColor(&black), getShortNameOfChessColor(&black));
			Assert::AreNotEqual(getLongNameOfChessColor(&white), getShortNameOfChessColor(&white));
		}
		TEST_METHOD(ChessTypeTest)
		{
			PieceType pawn = PieceType::Pawn;
			PieceType rook = PieceType::Rook;
			PieceType knight = PieceType::Knight;
			PieceType bishop = PieceType::Bishop;
			PieceType queen = PieceType::Queen;
			PieceType king = PieceType::King;

			std::string pawnLongString = "Pawn";
			std::string pawnShortString = "P";
			Assert::AreEqual(pawnLongString, getLongNameOfChessType(&pawn));
			Assert::AreEqual(pawnShortString, getShortNameOfChessType(&pawn));
			Assert::AreNotEqual(getShortNameOfChessType(&pawn), getLongNameOfChessType(&pawn));

			std::string rookLongString = "Rook";
			std::string rookShortString = "R";
			Assert::AreEqual(rookLongString, getLongNameOfChessType(&rook));
			Assert::AreEqual(rookShortString, getShortNameOfChessType(&rook));
			Assert::AreNotEqual(getShortNameOfChessType(&rook), getLongNameOfChessType(&rook));

			std::string knightLongString = "Knight";
			std::string knightShortString = "N";
			Assert::AreEqual(knightLongString, getLongNameOfChessType(&knight));
			Assert::AreEqual(knightShortString, getShortNameOfChessType(&knight));
			Assert::AreNotEqual(getShortNameOfChessType(&knight), getLongNameOfChessType(&knight));

			std::string bishopLongString = "Bishop";
			std::string bishopShortString = "B";
			Assert::AreEqual(bishopLongString, getLongNameOfChessType(&bishop));
			Assert::AreEqual(bishopShortString, getShortNameOfChessType(&bishop));
			Assert::AreNotEqual(getShortNameOfChessType(&bishop), getLongNameOfChessType(&bishop));

			std::string queenLongString = "Queen";
			std::string queenShortString = "Q";
			Assert::AreEqual(queenLongString, getLongNameOfChessType(&queen));
			Assert::AreEqual(queenShortString, getShortNameOfChessType(&queen));
			Assert::AreNotEqual(getShortNameOfChessType(&queen), getLongNameOfChessType(&queen));

			std::string kingLongString = "King";
			std::string kingShortString = "K";
			Assert::AreEqual(kingLongString, getLongNameOfChessType(&king));
			Assert::AreEqual(kingShortString, getShortNameOfChessType(&king));
			Assert::AreNotEqual(getShortNameOfChessType(&king), getLongNameOfChessType(&king));
		}
		TEST_METHOD(ChessTypeValueTest)
		{
			PieceType pawn = PieceType::Pawn;
			PieceType rook = PieceType::Rook;
			PieceType knight = PieceType::Knight;
			PieceType bishop = PieceType::Bishop;
			PieceType queen = PieceType::Queen;
			PieceType king = PieceType::King;

			Assert::AreEqual(USHRT_MAX, (int)getValueOfType(&king));
			Assert::AreEqual(9, (int)getValueOfType(&queen));
			Assert::AreEqual(5, (int)getValueOfType(&rook));
			Assert::AreEqual(3, (int)getValueOfType(&knight));
			Assert::AreEqual(3, (int)getValueOfType(&bishop));
			Assert::AreEqual(1, (int)getValueOfType(&pawn));
		}
		TEST_METHOD(ChessPieceTest)
		{
			ChessPiece wp(PieceType::Pawn, ChessColor::White);
			ChessPiece bp(PieceType::Pawn, ChessColor::Black);
			ChessPiece wr(PieceType::Rook, ChessColor::White);
			ChessPiece br(PieceType::Rook, ChessColor::Black);
			ChessPiece wk(PieceType::King, ChessColor::White);
			ChessPiece bk(PieceType::King, ChessColor::Black);
			ChessPiece wn(PieceType::Knight, ChessColor::White);
			ChessPiece bn(PieceType::Knight, ChessColor::Black);
			ChessPiece wb(PieceType::Bishop, ChessColor::White);
			ChessPiece bb(PieceType::Bishop, ChessColor::Black);
			ChessPiece wq(PieceType::Queen, ChessColor::White);
			ChessPiece bq(PieceType::Queen, ChessColor::Black);

			Assert::AreEqual((int)PieceType::Pawn, (int)wp.getType());
			Assert::AreEqual((int)PieceType::Pawn, (int)bp.getType());
			Assert::AreEqual((int)PieceType::Rook, (int)wr.getType());
			Assert::AreEqual((int)PieceType::Rook, (int)br.getType());
			Assert::AreEqual((int)PieceType::King, (int)wk.getType());
			Assert::AreEqual((int)PieceType::King, (int)bk.getType());
			Assert::AreEqual((int)PieceType::Knight, (int)wn.getType());
			Assert::AreEqual((int)PieceType::Knight, (int)bn.getType());
			Assert::AreEqual((int)PieceType::Bishop, (int)wb.getType());
			Assert::AreEqual((int)PieceType::Bishop, (int)bb.getType());
			Assert::AreEqual((int)PieceType::Queen, (int)wq.getType());
			Assert::AreEqual((int)PieceType::Queen, (int)bq.getType());

			Assert::AreEqual((int)ChessColor::White, (int)wp.getColor());
			Assert::AreEqual((int)ChessColor::Black, (int)bp.getColor());
			Assert::AreEqual((int)ChessColor::White, (int)wr.getColor());
			Assert::AreEqual((int)ChessColor::Black, (int)br.getColor());
			Assert::AreEqual((int)ChessColor::White, (int)wk.getColor());
			Assert::AreEqual((int)ChessColor::Black, (int)bk.getColor());
			Assert::AreEqual((int)ChessColor::White, (int)wn.getColor());
			Assert::AreEqual((int)ChessColor::Black, (int)bn.getColor());
			Assert::AreEqual((int)ChessColor::White, (int)wb.getColor());
			Assert::AreEqual((int)ChessColor::Black, (int)bb.getColor());
			Assert::AreEqual((int)ChessColor::White, (int)wq.getColor());
			Assert::AreEqual((int)ChessColor::Black, (int)bq.getColor());
		}
		TEST_METHOD(InvalidTypesAndColorForPieceTest)
		{
			PieceType noType = PieceType::NoType;
			ChessColor noColor = ChessColor::NoColor;
			PieceType rook = PieceType::Rook;
			ChessColor white = ChessColor::White;

			ChessPiece allInvalid = ChessPiece(noType, noColor);
			ChessPiece invalidType = ChessPiece(noType, white);
			ChessPiece invalidColor = ChessPiece(rook, noColor);
			ChessPiece empty = ChessPiece();
			ChessPiece valid = ChessPiece(rook, white);


			Assert::IsFalse(allInvalid.isValid());
			Assert::IsFalse(invalidType.isValid());
			Assert::IsFalse(invalidColor.isValid());
			Assert::IsFalse(empty.isValid());
			Assert::IsTrue(valid.isValid());
		}
		TEST_METHOD(DefaultConstructorPieceTest)
		{
			ChessPiece p = ChessPiece();
			Assert::IsFalse(p.isValid());
			Assert::AreEqual((int)ChessColor::NoColor, (int)p.getColor());
			Assert::AreEqual((int)PieceType::NoType, (int)p.getType());
		}
		TEST_METHOD(PieceEqualOperatorTest)
		{
			ChessPiece wr = ChessPiece(PieceType::Rook, ChessColor::White);
			ChessPiece anotherWr = ChessPiece(PieceType::Rook, ChessColor::White);

			ChessPiece br = ChessPiece(PieceType::Rook, ChessColor::Black);
			ChessPiece anotherBr = ChessPiece(PieceType::Rook, ChessColor::Black);

			Assert::IsFalse(wr == br);
			Assert::IsFalse(wr == anotherBr);

			Assert::IsTrue(wr == anotherWr);
			Assert::IsTrue(br == anotherBr);

			//doesnt work for some reason
			//Assert::AreNotEqual(wr, br);
		}
		TEST_METHOD(BoardSetGetAtPositionTest)
		{
			ChessBoardTest board = ChessBoardTest();
			ChessPiece wr = ChessPiece(PieceType::Rook, ChessColor::White);
			board.setPieceAt(&wr, &Coordinate('a', 1));
			ChessPiece gottenPiece = board.getAtPosition(&Coordinate('a', 1));
			Assert::IsTrue(wr == gottenPiece);
			gottenPiece = board.getAtPosition(&Coordinate('a', 2));
			Assert::IsFalse(wr == gottenPiece);

		}
		TEST_METHOD(NormalCoordinatesTest)
		{
			Coordinate a1 = Coordinate('a', 1);
			Coordinate h8 = Coordinate('h', 8);
			Assert::AreEqual(a1.getFileNormal(), 'a');
			Assert::AreEqual(h8.getFileNormal(), 'h');
			Assert::AreEqual((int)a1.getRankNormal(), 1);
			Assert::AreEqual((int)h8.getRankNormal(), 8);

			Assert::AreEqual((int)a1.getFileAsPosition(), 0);
			Assert::AreEqual((int)h8.getFileAsPosition(), 7);

			Assert::AreEqual((int)a1.getRankAsPosition(), 0);
			Assert::AreEqual((int)h8.getRankAsPosition(), 7);

			Coordinate arrA1 = Coordinate((short)0, (short)0);
			Coordinate arrH8 = Coordinate((short)7, (short)7);

			Assert::IsTrue(a1 == arrA1);
			Assert::IsTrue(h8 == arrH8);

			Assert::AreEqual(arrA1.getFileNormal(), 'a');
			Assert::AreEqual(arrH8.getFileNormal(), 'h');
			Assert::AreEqual((int)arrA1.getRankNormal(), 1);
			Assert::AreEqual((int)arrH8.getRankNormal(), 8);

			Assert::AreEqual((int)arrA1.getFileAsPosition(), 0);
			Assert::AreEqual((int)arrH8.getFileAsPosition(), 7);

			Assert::AreEqual((int)arrA1.getRankAsPosition(), 0);
			Assert::AreEqual((int)arrH8.getRankAsPosition(), 7);
		}
		TEST_METHOD(ValidCoordinatesTest)
		{
			Coordinate a1 = Coordinate('a', 1);
			Coordinate h8 = Coordinate('h', 8);
			Coordinate invalid1 = Coordinate('!', 1);
			Coordinate invalid2 = Coordinate('a', 9);
			Coordinate invalid3 = Coordinate('c', 22);

			Assert::IsTrue(a1.isValid());
			Assert::IsTrue(h8.isValid());
			Assert::IsFalse(invalid1.isValid());
			Assert::IsFalse(invalid2.isValid());
			Assert::IsFalse(invalid3.isValid());
		}
		TEST_METHOD(EqualCoordinatesTest)
		{
			Coordinate a1 = Coordinate('a', 1);
			Coordinate h8 = Coordinate('h', 8);
			Coordinate a1Copy = Coordinate('a', 1);
			Coordinate h8Copy = Coordinate('h', 8);
			Coordinate invalid1 = Coordinate('!', 1);
			Coordinate invalid2 = Coordinate('a', 9);
			Coordinate invalid3 = Coordinate('c', 22);

			Assert::IsTrue(a1 == a1Copy);
			Assert::IsFalse(a1 != a1Copy);

			Assert::IsTrue(h8 == h8Copy);
			Assert::IsFalse(h8 != h8Copy);

			Assert::IsFalse(a1 == h8);
			Assert::IsTrue(a1 != h8);

			Assert::IsFalse(a1 == invalid1);
			Assert::IsTrue(a1 != invalid1);

			Assert::IsFalse(a1 == invalid2);
			Assert::IsTrue(a1 != invalid2);

			Assert::IsFalse(a1 == invalid3);
			Assert::IsTrue(a1 != invalid3);
		}
		TEST_METHOD(MoveTest)
		{
			Move defaultConstructor = Move();
			Assert::IsFalse(defaultConstructor.getDestination().isValid());
			Assert::IsFalse(defaultConstructor.getStart().isValid());
			Assert::IsFalse(defaultConstructor.isValid());

			Move move = Move(
				&Coordinate('a', 1),
				&Coordinate('b', 2));

			Assert::IsTrue(move.getStart().isValid());
			Assert::IsTrue(move.getDestination().isValid());
			Assert::IsFalse((move.getDestination()) == (move.getStart()));

			Assert::IsTrue(Coordinate('a', 1) == (move.getStart()));
			Assert::IsTrue(Coordinate('b', 2) == (move.getDestination()));

			Assert::IsTrue(move.isValid());
		}
		TEST_METHOD(defaultBoardSetupTest)
		{
			ChessBoardTest board = ChessBoardTest();
			Assert::IsTrue(
				(board.getAtPosition(&Coordinate('a', 1))) ==
				ChessPiece(PieceType::Rook, ChessColor::White));
			Assert::IsTrue(
				(board.getAtPosition(&Coordinate('b', 1))) ==
				ChessPiece(PieceType::Knight, ChessColor::White));
			Assert::IsTrue(
				(board.getAtPosition(&Coordinate('c', 1))) ==
				ChessPiece(PieceType::Bishop, ChessColor::White));
			Assert::IsTrue(
				(board.getAtPosition(&Coordinate('d', 1))) ==
				ChessPiece(PieceType::Queen, ChessColor::White));
			Assert::IsTrue(
				(board.getAtPosition(&Coordinate('e', 1))) ==
				ChessPiece(PieceType::King, ChessColor::White));
			Assert::IsTrue(
				(board.getAtPosition(&Coordinate('f', 1))) ==
				ChessPiece(PieceType::Bishop, ChessColor::White));
			Assert::IsTrue(
				(board.getAtPosition(&Coordinate('g', 1))) ==
				ChessPiece(PieceType::Knight, ChessColor::White));
			Assert::IsTrue(
				(board.getAtPosition(&Coordinate('h', 1))) ==
				ChessPiece(PieceType::Rook, ChessColor::White));
			for (char file = 'a'; file <= 'h'; file++)
			{
				Assert::IsTrue(
					(board.getAtPosition(&Coordinate(file, 2))) ==
					ChessPiece(PieceType::Pawn, ChessColor::White));
				for (int rank = 3; rank <= 6; rank++)
				{
					Assert::IsFalse(board.getAtPosition(&Coordinate(file, rank)).isValid());
					Assert::IsTrue(
						(board.getAtPosition(&Coordinate(file, rank))) ==
						ChessPiece(PieceType::NoType, ChessColor::NoColor));
				}
				Assert::IsTrue(
					(board.getAtPosition(&Coordinate(file, 7))) ==
					ChessPiece(PieceType::Pawn, ChessColor::Black));
			}
			Assert::IsTrue(
				(board.getAtPosition(&Coordinate('a', 8))) ==
				ChessPiece(PieceType::Rook, ChessColor::Black));
			Assert::IsTrue(
				(board.getAtPosition(&Coordinate('b', 8))) ==
				ChessPiece(PieceType::Knight, ChessColor::Black));
			Assert::IsTrue(
				(board.getAtPosition(&Coordinate('c', 8))) ==
				ChessPiece(PieceType::Bishop, ChessColor::Black));
			Assert::IsTrue(
				(board.getAtPosition(&Coordinate('d', 8))) ==
				ChessPiece(PieceType::Queen, ChessColor::Black));
			Assert::IsTrue(
				(board.getAtPosition(&Coordinate('e', 8))) ==
				ChessPiece(PieceType::King, ChessColor::Black));
			Assert::IsTrue(
				(board.getAtPosition(&Coordinate('f', 8))) ==
				ChessPiece(PieceType::Bishop, ChessColor::Black));
			Assert::IsTrue(
				(board.getAtPosition(&Coordinate('g', 8))) ==
				ChessPiece(PieceType::Knight, ChessColor::Black));
			Assert::IsTrue(
				(board.getAtPosition(&Coordinate('h', 8))) ==
				ChessPiece(PieceType::Rook, ChessColor::Black));
		}
		TEST_METHOD(chessBoardClearTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();
			for (char file = 'a'; file <= 'h'; file++)
			{
				for (int rank = 1; rank <= 8; rank++)
				{
					Assert::IsFalse(board.getAtPosition(&Coordinate(file, rank)).isValid());
					Assert::IsTrue(
						(board.getAtPosition(&Coordinate(file, rank))) ==
						ChessPiece(PieceType::NoType, ChessColor::NoColor));
				}
			}
		}
		TEST_METHOD(boardGetAllMovesNoMovesAvailible)
		{
			ChessBoardTest board = ChessBoardTest();
			ChessColor white = ChessColor::White;
			ChessColor black = ChessColor::Black;

			board.clearBoard();
			
			std::vector<Move*> possibleMoves = board.getAllMoves(&white);
			Assert::AreEqual((int)possibleMoves.size(), 0);

			possibleMoves = board.getAllMoves(&white);
			Assert::AreEqual((int)possibleMoves.size(), 0);
		}
		TEST_METHOD(boardGetSimpleMovementOfPiecesTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			Coordinate coord = Coordinate('a', 1);

			//test moves at a1
			std::vector<Move*> allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Rook, ChessColor::White),
					&coord);
			Assert::AreEqual(14, (int)allMoves.size());

			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Bishop, ChessColor::White),
					&coord);
			Assert::AreEqual(7, (int)allMoves.size());

			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Queen, ChessColor::White),
					&coord);
			Assert::AreEqual(21, (int)allMoves.size());

			coord = Coordinate('e', 4);

			//test moves on e4 without obstacles
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Rook, ChessColor::White),
					&coord);
			Assert::AreEqual(14, (int)allMoves.size());

			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Bishop, ChessColor::White),
					&coord);
			Assert::AreEqual(13, (int)allMoves.size());

			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Queen, ChessColor::White),
					&coord);
			Assert::AreEqual(27, (int)allMoves.size());

			//test moves on e4 with enemy obstacle
			board.setPieceAt(
				&ChessPiece(PieceType::Rook, ChessColor::Black),
				&Coordinate('c', 4));

			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Rook, ChessColor::White),
					&coord);
			Assert::AreEqual(12, (int)allMoves.size());

			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Bishop, ChessColor::White),
					&coord);
			Assert::AreEqual(13, (int)allMoves.size());

			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Queen, ChessColor::White),
					&coord);
			Assert::AreEqual(25, (int)allMoves.size());

			//test moves on e4 with friendly obstacle
			board.setPieceAt(
				&ChessPiece(PieceType::Rook, ChessColor::White),
				&Coordinate('c', 4));

			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Rook, ChessColor::White),
					&coord);
			Assert::AreEqual(11, (int)allMoves.size());

			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Bishop, ChessColor::White),
					&coord);
			Assert::AreEqual(13, (int)allMoves.size());

			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Queen, ChessColor::White),
					&coord);
			Assert::AreEqual(24, (int)allMoves.size());
		}
		TEST_METHOD(boardGetMovementOfKnightTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			Coordinate start = Coordinate('a', 1);
			std::vector<Move*> allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Knight, ChessColor::White),
					&start);
			Assert::AreEqual(2, (int)allMoves.size());

			start = Coordinate('e', 4);
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Knight, ChessColor::White),
					&start);
			Assert::AreEqual(8, (int)allMoves.size());

			start = Coordinate('b', 7);
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Knight, ChessColor::White),
					&start);
			Assert::AreEqual(4, (int)allMoves.size());

			start = Coordinate('d', 7);
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Knight, ChessColor::White),
					&start);
			Assert::AreEqual(6, (int)allMoves.size());
		}
		TEST_METHOD(boardGetMovementOfPawnForwardTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			//normal start position 2 possible moves
			//white
			std::vector<Move*> allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::White),
					&Coordinate('a', 2));
			Assert::AreEqual(2, (int)allMoves.size());
			//black
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::Black),
					&Coordinate('a', 7));
			Assert::AreEqual(2, (int)allMoves.size());

			//normal start position
			//cannot move, because blocked field in front
			//white
			board.setPieceAt(
				&ChessPiece(PieceType::Pawn, ChessColor::Black),
				&Coordinate('a', 3));
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::White),
					&Coordinate('a', 2));
			Assert::AreEqual(0, (int)allMoves.size());
			//black
			board.clearBoard();
			board.setPieceAt(
				&ChessPiece(PieceType::Pawn, ChessColor::White),
				&Coordinate('a', 6));
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::Black),
					&Coordinate('a', 7));
			Assert::AreEqual(0, (int)allMoves.size());

			//normal start position
			//can move 1, because the 2nd field move is blocked
			//white
			board.clearBoard();
			board.setPieceAt(
				&ChessPiece(PieceType::Pawn, ChessColor::Black),
				&Coordinate('a', 4));
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::White),
					&Coordinate('a', 2));
			Assert::AreEqual(1, (int)allMoves.size());
			//black
			board.clearBoard();
			board.setPieceAt(
				&ChessPiece(PieceType::Pawn, ChessColor::White),
				&Coordinate('a', 5));
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::Black),
					&Coordinate('a', 7));
			Assert::AreEqual(1, (int)allMoves.size());

			//not at start position
			//can move one forward
			//white
			board.clearBoard();
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::White),
					&Coordinate('d', 5));
			Assert::AreEqual(1, (int)allMoves.size());
			//black
			board.clearBoard();
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::Black),
					&Coordinate('d', 4));
			Assert::AreEqual(1, (int)allMoves.size());

			//unrealistic scenario, because pawn should transform into another piece
			//pawn on the other side and cannot move, because board ends
			//white
			board.clearBoard();
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::White),
					&Coordinate('d', 8));
			Assert::AreEqual(0, (int)allMoves.size());
			//black
			board.clearBoard();
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::Black),
					&Coordinate('d', 1));
			Assert::AreEqual(0, (int)allMoves.size());
		}
		TEST_METHOD(boardGetMovementOfPawnTakingAPieceTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			//not start position
			//move forward is blocked, but can take a piece
			//white
			board.setPieceAt(
				&ChessPiece(PieceType::Pawn, ChessColor::Black),
				&Coordinate('a', 5));
			board.setPieceAt(
				&ChessPiece(PieceType::Pawn, ChessColor::Black),
				&Coordinate('b', 5));
			std::vector<Move*> allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::White),
					&Coordinate('a', 4));
			Assert::AreEqual(1, (int)allMoves.size());
			//black
			board.clearBoard();
			board.setPieceAt(
				&ChessPiece(PieceType::Pawn, ChessColor::White),
				&Coordinate('a', 4));
			board.setPieceAt(
				&ChessPiece(PieceType::Pawn, ChessColor::White),
				&Coordinate('b', 4));
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::Black),
					&Coordinate('a', 5));
			Assert::AreEqual(1, (int)allMoves.size());

			//on start position
			//can take left and right
			//can move 2 forward -> nothing blocked
			//white
			board.clearBoard();
			board.setPieceAt(
				&ChessPiece(PieceType::Pawn, ChessColor::Black),
				&Coordinate('d', 3));
			board.setPieceAt(
				&ChessPiece(PieceType::Pawn, ChessColor::Black),
				&Coordinate('f', 3));
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::White),
					&Coordinate('e', 2));
			Assert::AreEqual(4, (int)allMoves.size());
			//black
			board.clearBoard();
			board.setPieceAt(
				&ChessPiece(PieceType::Pawn, ChessColor::White),
				&Coordinate('d', 6));
			board.setPieceAt(
				&ChessPiece(PieceType::Pawn, ChessColor::White),
				&Coordinate('f', 6));
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::Black),
					&Coordinate('e', 7));
			Assert::AreEqual(4, (int)allMoves.size());

			//on start position
			//front blocked by opponent piece
			//cannot take right piece, because it is from the same color
			//cannot take left because no enemy piece is there
			board.clearBoard();
			board.setPieceAt(
				&ChessPiece(PieceType::Pawn, ChessColor::Black),
				&Coordinate('c', 3));
			board.setPieceAt(
				&ChessPiece(PieceType::Pawn, ChessColor::White),
				&Coordinate('d', 3));
			allMoves = board.getAllMovesOfPiece(
				&ChessPiece(PieceType::Pawn, ChessColor::White),
				&Coordinate('c', 2));
			Assert::AreEqual(0, (int)allMoves.size());
		}
		TEST_METHOD(moveEqualTest)
		{
			Move first = Move(
				&Coordinate('a', 1),
				&Coordinate('a', 2));
			Move second = Move(
				&Coordinate('a', 1),
				&Coordinate('a', 2));
			Assert::IsTrue(first == second);
			Assert::IsFalse(first != second);

			Move third = Move(
				&Coordinate('a', 1),
				&Coordinate('a', 3));
			Assert::IsFalse(first == third);
			Assert::IsFalse(second == third);
			Assert::IsTrue(first != third);
			Assert::IsTrue(second != third);
		}
		TEST_METHOD(boardLastMoveTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			//Even if the move is not set, the last move should exist. But its an invalid move
			Move move = Move();
			Assert::IsTrue(move == board.getLastMove());

			//An invalid move is still accpeted as last move,
			//because it will be only set when it is valid
			move = Move(
				&Coordinate('a', 1),
				&Coordinate('a', 1));
			board.setLastMove(&move);
			Assert::IsTrue(move == board.getLastMove());

			//obviously a valid move is accepted as last move
			move = Move(
				&Coordinate('a', 1),
				&Coordinate('a', 2));
			board.setLastMove(&move);

			Assert::IsTrue(move == board.getLastMove());
		}
		TEST_METHOD(boardGetMovementOfPawnEnPassantTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			//only 2 pieces on the board
			//can do 2 moves: en passant and move forward
			//white
			board.setPieceAt(
				&ChessPiece(PieceType::Pawn, ChessColor::Black),
				&Coordinate('a', 5));
			board.setLastMove(&Move(
				&Coordinate('a', 7),
				&Coordinate('a', 5)));

			std::vector<Move*> allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::White),
					&Coordinate('b', 5));
			Assert::AreEqual(2, (int)allMoves.size());
			Assert::IsTrue(
				containsMove(allMoves,
					&Move(
						&Coordinate('b', 5),
						&Coordinate('a', 6)
					)));
			//black
			board.clearBoard();
			board.setPieceAt(
				&ChessPiece(PieceType::Pawn, ChessColor::White),
				&Coordinate('a', 4));
			board.setLastMove(&Move(
				&Coordinate('a', 2),
				&Coordinate('a', 4)));
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::Black),
					&Coordinate('b', 4));
			Assert::AreEqual(2, (int)allMoves.size());
			Assert::IsTrue(
				containsMove(allMoves,
					&Move(
						&Coordinate('b', 4),
						&Coordinate('a', 3)
					)));

			//cannot do en passant.
			//move is correct, but not the right piece
			//white
			board.setPieceAt(
				&ChessPiece(PieceType::Rook, ChessColor::Black),
				&Coordinate('a', 5));
			board.setLastMove(&Move(
				&Coordinate('a', 7),
				&Coordinate('a', 5)));

			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::White),
					&Coordinate('b', 5));
			Assert::AreEqual(1, (int)allMoves.size());
			//black
			board.clearBoard();
			board.setPieceAt(
				&ChessPiece(PieceType::Rook, ChessColor::White),
				&Coordinate('a', 4));
			board.setLastMove(&Move(
				&Coordinate('a', 2),
				&Coordinate('a', 4)));
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::Black),
					&Coordinate('b', 4));
			Assert::AreEqual(1, (int)allMoves.size());

			//cannot do en passant.
			//pawn didnt do a double move in the last turn
			//white
			board.clearBoard();
			board.setPieceAt(
				&ChessPiece(PieceType::Pawn, ChessColor::Black),
				&Coordinate('a', 5));
			board.setLastMove(&Move(
				&Coordinate('a', 6),
				&Coordinate('a', 5)));
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::White),
					&Coordinate('b', 5));
			Assert::AreEqual(1, (int)allMoves.size());
		}
		TEST_METHOD(boardGetMovementOfKingTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			//king is free to move
			std::vector<Move*> allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::King, ChessColor::White),
					&Coordinate('e', 4));
			Assert::AreEqual(8, (int)allMoves.size());

			//king is in a corner
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::King, ChessColor::White),
					&Coordinate('a', 1));
			Assert::AreEqual(3, (int)allMoves.size());

			//king is on the side of the board
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::King, ChessColor::White),
					&Coordinate('e', 1));
			Assert::AreEqual(5, (int)allMoves.size());

			//king can take a piece
			board.clearBoard();
			board.setPieceAt(
				&ChessPiece(PieceType::Knight, ChessColor::Black),
				&Coordinate('e', 5));
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::King, ChessColor::White),
					&Coordinate('e', 4));
			Assert::AreEqual(8, (int)allMoves.size());

			//king cannot take a piece of the same color
			board.clearBoard();
			board.setPieceAt(
				&ChessPiece(PieceType::Knight, ChessColor::White),
				&Coordinate('e', 5));
			allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::King, ChessColor::White),
					&Coordinate('e', 4));
			Assert::AreEqual(7, (int)allMoves.size());
		}
		TEST_METHOD(raycastOptionsTest)
		{
			RayCastOptions options = RayCastOptions();

			Assert::IsTrue(options.getOrigin() == Coordinate());
			Assert::AreEqual(options.getMaxIterations(), (short)-1);
			Assert::IsFalse(options.getNeedsMoveList());
			Assert::IsTrue(options.getColor() == ChessColor::NoColor);
			Assert::IsTrue(options.getImaginaryMove() == Move());

			Coordinate start = Coordinate('a', 1);
			Move imaginaryMove = Move(
				&Coordinate('a', 1),
				&Coordinate('a', 2));
			ChessColor col = ChessColor::White;
			options = RayCastOptions(
				&start,
				(short)1,
				true,
				&col
			);
			options.setImaginaryMove(&imaginaryMove);

			Assert::IsTrue(options.getOrigin() == start);
			Assert::AreEqual(options.getMaxIterations(), (short)1);
			Assert::IsTrue(options.getNeedsMoveList());
			Assert::IsTrue(options.getColor() == col);
			Assert::IsTrue(options.getImaginaryMove() == imaginaryMove);

			Coordinate newStartCoord = Coordinate('h', 2);
			options.setStart(&newStartCoord);
			options.setMaxIterations(3);
			options.setNeedsMoveList(false);
			ChessColor newColor = ChessColor::Black;
			options.setColor(&newColor);

			Assert::IsTrue(newStartCoord == options.getOrigin());
			Assert::AreEqual((short)3, options.getMaxIterations());
			Assert::IsFalse(options.getNeedsMoveList());
			Assert::IsTrue(options.getColor() == newColor);

			options = RayCastOptions(&start, false, &col);
			Assert::AreEqual((short)-1, options.getMaxIterations());
		}
		TEST_METHOD(raycastResultTest)
		{
			RayCastResult result = RayCastResult();

			Assert::IsTrue(result.getRayCastMoves() == std::vector<Move*>());
			Assert::AreEqual((int)result.getRayCastMoves().size(), 0);

			result = RayCastResult(result.getRayCastMoves());
			Assert::AreEqual((int)result.getRayCastMoves().size(), 0);

			std::vector<Move*> movesToAdd = std::vector<Move*>();
			movesToAdd.push_back(new Move(
				&Coordinate('b', 1),
				&Coordinate('c', 2)
			));
			movesToAdd.push_back(new Move(
				&Coordinate('d', 1),
				&Coordinate('e', 2)
			));

			result = RayCastResult(movesToAdd);

			//see if list didnt change
			Assert::AreEqual(2, (int)movesToAdd.size());
			//see if it is added
			Assert::AreEqual(2, (int)result.getRayCastMoves().size());

		}
		TEST_METHOD(addingRayCastResultTest)
		{
			std::vector<Move*> rcMoves1 = {
				new Move(&Coordinate('a', 1), &Coordinate('a', 2))
			};
			RayCastResult rcResult1 = RayCastResult(rcMoves1);

			std::vector<Move*> rcMoves2 = {
				new Move(&Coordinate('a', 2), &Coordinate('a', 3))
			};
			RayCastResult rcResult2 = RayCastResult(rcMoves2);

			//add the lists and do the or operator on the "isunderattack"
			RayCastResult addedResult = rcResult1 + rcResult2;

			//the added moves should be all two lists combined
			Assert::AreEqual((int)addedResult.getRayCastMoves().size(), 2);

			//the combnined result should be containing both values
			Assert::IsTrue(containsMove(addedResult.getRayCastMoves(),
				&Move(&Coordinate('a', 1), &Coordinate('a', 2))));
			Assert::IsTrue(containsMove(addedResult.getRayCastMoves(),
				&Move(&Coordinate('a', 2), &Coordinate('a', 3))));

			//the other rcresults should not be changed in any way
			Assert::AreEqual((int)rcResult1.getRayCastMoves().size(), 1);
			Assert::IsTrue(containsMove(rcResult1.getRayCastMoves(),
				&Move(&Coordinate('a', 1), &Coordinate('a', 2))));
			Assert::AreEqual((int)rcResult2.getRayCastMoves().size(), 1);
			Assert::IsTrue(containsMove(rcResult2.getRayCastMoves(),
				&Move(&Coordinate('a', 2), &Coordinate('a', 3))));
		}
		TEST_METHOD(getAtPositionWithMoveDoneTest)
		{
			ChessBoardTest board = ChessBoardTest();

			//position is on move start
			//so the piece moved away from that spot and is no longer there
			board.clearBoard();
			Coordinate pos1 = Coordinate('a', 1);
			Coordinate pos2 = Coordinate('a', 2);
			ChessPiece piece = ChessPiece(PieceType::Rook, ChessColor::White);
			board.setPieceAt(&piece, &pos1);
			Move move = Move(&pos1, &pos2);
			Assert::IsFalse(board.getAtPostitionWithMoveDone(&pos1, &move).isValid());

			//position is on move destination
			//the piece from the start position is now there
			board.clearBoard();
			pos1 = Coordinate('a', 3);
			pos2 = Coordinate('a', 4);
			piece = ChessPiece(PieceType::Rook, ChessColor::White);
			board.setPieceAt(&piece, &pos1);
			move = Move(&pos1, &pos2);
			Assert::IsTrue(board.getAtPostitionWithMoveDone(&pos2, &move) == piece);

			//position is not effected by move
			board.clearBoard();
			pos1 = Coordinate('d', 3);
			pos2 = Coordinate('d', 4);
			piece = ChessPiece(PieceType::Rook, ChessColor::White);
			board.setPieceAt(&piece, &pos1);
			move = Move(&pos1, &pos2);
			Coordinate pos3 = Coordinate('a', 5);
			ChessPiece anotherPiece = ChessPiece(PieceType::Rook, ChessColor::Black);
			board.setPieceAt(&anotherPiece, &pos3);
			Assert::IsTrue(board.getAtPostitionWithMoveDone(&pos3, &move) == anotherPiece);

			//en passant pawn is taken by the move
			board.clearBoard();
			pos1 = Coordinate('b', 5);
			pos2 = Coordinate('a', 6);
			pos3 = Coordinate('a', 5);
			piece = ChessPiece(PieceType::Pawn, ChessColor::White);
			board.setPieceAt(&piece, &pos1);
			anotherPiece = ChessPiece(PieceType::Pawn, ChessColor::Black);
			board.setPieceAt(&anotherPiece, &pos3);
			move = Move(&pos1, &pos2);
			Assert::IsFalse(board.getAtPostitionWithMoveDone(&pos3, &move).isValid());

			//castling move
			//white short castling
			board.clearBoard();

			Coordinate kingPos = Coordinate('e', 1);
			ChessPiece king = ChessPiece(PieceType::King, ChessColor::White);
			board.setPieceAt(&king, &kingPos);

			Coordinate rookPos = Coordinate('h', 1);
			ChessPiece rook = ChessPiece(PieceType::Rook, ChessColor::White);
			board.setPieceAt(&rook, &rookPos);

			Coordinate kingFinalPos = Coordinate('g', 1);
			Coordinate rookFinalPos = Coordinate('f', 1);

			move = Move(&kingPos, &kingFinalPos);
			Assert::IsFalse(board.getAtPostitionWithMoveDone(&kingPos, &move).isValid());
			Assert::IsFalse(board.getAtPostitionWithMoveDone(&rookPos, &move).isValid());
			Assert::IsTrue(board.getAtPostitionWithMoveDone(&rookFinalPos, &move) == rook);
			Assert::IsTrue(board.getAtPostitionWithMoveDone(&kingFinalPos, &move) == king);

			//black long castle
			board.clearBoard();
			rookPos = Coordinate('a', 8);
			rookFinalPos = Coordinate('d', 8);
			rook = ChessPiece(PieceType::Rook, ChessColor::Black);
			board.setPieceAt(&rook, &rookPos);

			kingPos = Coordinate('e', 8);
			kingFinalPos = Coordinate('c', 8);
			king = ChessPiece(PieceType::King, ChessColor::Black);
			board.setPieceAt(&king, &kingPos);

			move = Move(&kingPos, &kingFinalPos);

			Assert::IsFalse(board.getAtPostitionWithMoveDone(&kingPos, &move).isValid());
			Assert::IsFalse(board.getAtPostitionWithMoveDone(&rookPos, &move).isValid());

			Coordinate spaceThatShouldNotBeOccupiedAfterCastling = Coordinate('b', 8);
			Assert::IsFalse(board.getAtPostitionWithMoveDone(
				&spaceThatShouldNotBeOccupiedAfterCastling, &move).isValid());

			Assert::IsTrue(board.getAtPostitionWithMoveDone(&rookFinalPos, &move) == rook);
			Assert::IsTrue(board.getAtPostitionWithMoveDone(&kingFinalPos, &move) == king);

			board.clearBoard();
			Coordinate validCoord = Coordinate('a', 1);
			Coordinate invalidCoord = Coordinate('a', 9);
			piece = ChessPiece(PieceType::Rook, ChessColor::White);
			board.setPieceAt(&piece, &validCoord);
			move = Move(&invalidCoord, &validCoord);
			Assert::IsTrue(board.getAtPosition(&validCoord) == piece);
			Assert::IsTrue(
				board.getAtPosition(&validCoord) ==
				board.getAtPostitionWithMoveDone(&validCoord, &move));
		}
		TEST_METHOD(executeSingleRayCastTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			//try a diagonal raycast
			Coordinate start = Coordinate('a', 1);
			ChessColor rcColor = ChessColor::White;

			RayCastOptions rcOptions = RayCastOptions(
				&start,
				-1,
				true,
				&rcColor
			);

			RayCastResult rcResult = board.executeSingleRayCast(&rcOptions, 1, 1);

			Assert::AreEqual(7, (int)rcResult.getRayCastMoves().size());

			//try a raycast with the a same colored piece in the way
			board.clearBoard();

			ChessPiece sameColorPieceInTheWay =
				ChessPiece(PieceType::Rook, ChessColor::White);
			Coordinate posWherePieceIsInTheWay =
				Coordinate('e', 5);
			board.setPieceAt(&sameColorPieceInTheWay, &posWherePieceIsInTheWay);

			rcResult = board.executeSingleRayCast(&rcOptions, 1, 1);

			Assert::AreEqual(3, (int)rcResult.getRayCastMoves().size());

			//try a raycast with the a different colored piece in the way
			board.clearBoard();

			ChessPiece differentColorPieceInTheWay =
				ChessPiece(PieceType::Rook, ChessColor::Black);
			Coordinate posWherePieceIsInTheWay2 =
				Coordinate('e', 5);
			board.setPieceAt(&differentColorPieceInTheWay, &posWherePieceIsInTheWay2);

			rcResult = board.executeSingleRayCast(&rcOptions, 1, 1);

			Assert::AreEqual(4, (int)rcResult.getRayCastMoves().size());

			//try a raycast with a max iteration of 1
			board.clearBoard();
			rcOptions.setMaxIterations(1);
			rcResult = board.executeSingleRayCast(&rcOptions, 1, 1);
			Assert::AreEqual(1, (int)rcResult.getRayCastMoves().size());

			//try a raycast with a max iteration of 1
			//but the one place is occupied by a the same colored piece
			board.clearBoard();
			rcOptions.setMaxIterations(1);

			sameColorPieceInTheWay = ChessPiece(PieceType::Rook, ChessColor::White);
			posWherePieceIsInTheWay = Coordinate('b', 2);
			board.setPieceAt(&sameColorPieceInTheWay, &posWherePieceIsInTheWay);

			rcResult = board.executeSingleRayCast(&rcOptions, 1, 1);
			Assert::AreEqual(0, (int)rcResult.getRayCastMoves().size());

			//try a raycast with "move list not needed" option on "false"
			//it is expected, that there will be no moves.
			board.clearBoard();
			ChessColor white = ChessColor::White;
			rcOptions = RayCastOptions(
				&start,
				-1,
				false,
				&white);
			rcResult = board.executeSingleRayCast(&rcOptions, 0, 1);
			Assert::AreEqual(0, (int)rcResult.getRayCastMoves().size());

			//try a raycast with "move list not needed" option on "false"
			//it is expected, that the list contains one move.
			//that is because you need at least one move to calculate if the field gets attacked
			board.clearBoard();
			white = ChessColor::White;
			rcOptions = RayCastOptions(
				&start,
				-1,
				false,
				&white);
			rcResult = board.executeSingleRayCast(&rcOptions, 0, 1);
			Assert::AreEqual(0, (int)rcResult.getRayCastMoves().size());
		}
		TEST_METHOD(executeSpecificRayCastsTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			PieceType rookType = PieceType::Rook;
			Coordinate start = Coordinate('d', 1);
			ChessColor white = ChessColor::White;
			RayCastOptions options = RayCastOptions(
				&start,
				-1,
				true,
				&white
			);

			RayCastResult rcResult = board.executeRayCast(&rookType, &options, false);

			Assert::AreEqual(14, (int)rcResult.getRayCastMoves().size());
		}
		TEST_METHOD(clearPieceAtPositionTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();
			Coordinate coord = Coordinate('a', 1);
			ChessPiece piece = ChessPiece(PieceType::Rook, ChessColor::White);
			board.setPieceAt(&piece, &coord);
			Assert::IsTrue(board.getAtPosition(&coord) == piece);
			board.clearPieceAt(&coord);
			Assert::IsTrue(board.getAtPosition(&coord) == ChessPiece());
		}
		TEST_METHOD(fieldIsUnderAttack)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			ChessColor white = ChessColor::White;
			ChessColor black = ChessColor::Black;

			Coordinate fieldToAttack = Coordinate('e', 4);

			//a single knight attacks
			Coordinate enemyPos = Coordinate('f', 6);
			ChessPiece enemyPiece = ChessPiece(PieceType::Knight, black);
			board.setPieceAt(&enemyPiece, &enemyPos);

			Assert::IsTrue(board.fieldIsUnderAttack(&fieldToAttack, &white));

			//3 pawns protect the king - knight can still attack
			Coordinate blockingPos1 = Coordinate('e', 5);
			Coordinate blockingPos2 = Coordinate('f', 5);
			Coordinate blockingPos3 = Coordinate('f', 4);
			ChessPiece blockingPiece = ChessPiece(PieceType::Pawn, white);
			board.setPieceAt(&blockingPiece, &blockingPos1);
			board.setPieceAt(&blockingPiece, &blockingPos2);
			board.setPieceAt(&blockingPiece, &blockingPos3);

			Assert::IsTrue(board.fieldIsUnderAttack(&fieldToAttack, &white));
			board.clearBoard();

			//pawn attacks
			enemyPos = Coordinate('f', 5);
			enemyPiece = ChessPiece(PieceType::Pawn, black);
			board.setPieceAt(&enemyPiece, &enemyPos);

			Assert::IsTrue(board.fieldIsUnderAttack(&fieldToAttack, &white));
			board.clearPieceAt(&enemyPos);

			enemyPos = Coordinate('d', 5);
			enemyPiece = ChessPiece(PieceType::Pawn, black);
			board.setPieceAt(&enemyPiece, &enemyPos);

			Assert::IsTrue(board.fieldIsUnderAttack(&fieldToAttack, &white));
			board.clearPieceAt(&enemyPos);

			//pawn does not attack - stands before piece
			enemyPos = Coordinate('e', 5);
			enemyPiece = ChessPiece(PieceType::Pawn, black);
			board.setPieceAt(&enemyPiece, &enemyPos);

			Assert::IsFalse(board.fieldIsUnderAttack(&fieldToAttack, &white));
			board.clearPieceAt(&enemyPos);

			//pawn does not attack - stands behind piece
			enemyPos = Coordinate('f', 3);
			enemyPiece = ChessPiece(PieceType::Pawn, black);
			board.setPieceAt(&enemyPiece, &enemyPos);

			Assert::IsFalse(board.fieldIsUnderAttack(&fieldToAttack, &white));

			enemyPiece = ChessPiece(PieceType::Pawn, white);
			board.setPieceAt(&enemyPiece, &enemyPos);
			Assert::IsTrue(board.fieldIsUnderAttack(&fieldToAttack, &black));
			board.clearPieceAt(&enemyPos);

			//rook attacks
			enemyPos = Coordinate('e', 1);
			enemyPiece = ChessPiece(PieceType::Rook, black);
			board.setPieceAt(&enemyPiece, &enemyPos);

			Assert::IsTrue(board.fieldIsUnderAttack(&fieldToAttack, &white));

			//rook does not attack - stands before piece
			blockingPos1 = Coordinate('e', 3);
			blockingPiece = ChessPiece(PieceType::Bishop, white);
			board.setPieceAt(&blockingPiece, &blockingPos1);

			Assert::IsFalse(board.fieldIsUnderAttack(&fieldToAttack, &white));
			board.clearBoard();

			//gets attacked by king
			enemyPos = Coordinate('e', 3);
			enemyPiece = ChessPiece(PieceType::King, black);
			board.setPieceAt(&enemyPiece, &enemyPos);

			Assert::IsTrue(board.fieldIsUnderAttack(&fieldToAttack, &white));
			board.clearPieceAt(&enemyPos);

			enemyPos = Coordinate('d', 3);
			enemyPiece = ChessPiece(PieceType::King, black);
			board.setPieceAt(&enemyPiece, &enemyPos);

			Assert::IsTrue(board.fieldIsUnderAttack(&fieldToAttack, &white));
			board.clearBoard();

			//gets attacked by bishop
			enemyPos = Coordinate('a', 8);
			enemyPiece = ChessPiece(PieceType::Bishop, white);
			board.setPieceAt(&enemyPiece, &enemyPos);

			Assert::IsTrue(board.fieldIsUnderAttack(&fieldToAttack, &black));

			enemyPiece = ChessPiece(PieceType::Bishop, black);
			board.setPieceAt(&enemyPiece, &enemyPos);

			Assert::IsTrue(board.fieldIsUnderAttack(&fieldToAttack, &white));

			//bishop is blocked by pawn
			blockingPos1 = Coordinate('b', 7);
			blockingPiece = ChessPiece(PieceType::Pawn, white);
			board.setPieceAt(&blockingPiece, &blockingPos1);

			Assert::IsFalse(board.fieldIsUnderAttack(&fieldToAttack, &white));

			//bishop blocked by same colored rook
			blockingPiece = ChessPiece(PieceType::Rook, black);
			board.setPieceAt(&blockingPiece, &blockingPos1);

			Assert::IsFalse(board.fieldIsUnderAttack(&fieldToAttack, &white));

			//queen attacks piece straight
			enemyPos = Coordinate('g', 4);
			enemyPiece = ChessPiece(PieceType::Queen, black);
			board.setPieceAt(&enemyPiece, &enemyPos);

			Assert::IsTrue(board.fieldIsUnderAttack(&fieldToAttack, &white));

			//queen gets blocked by same colored Pawn
			blockingPiece = ChessPiece(PieceType::Pawn, black);
			blockingPos1 = Coordinate('f', 4);
			board.setPieceAt(&blockingPiece, &blockingPos1);

			Assert::IsFalse(board.fieldIsUnderAttack(&fieldToAttack, &white));
			board.clearBoard();

			//queen attacks piece diagonal
			enemyPos = Coordinate('h', 7);
			board.setPieceAt(&enemyPiece, &enemyPos);

			Assert::IsTrue(board.fieldIsUnderAttack(&fieldToAttack, &white));

			//queen gets blocked by opposite colored piece

			blockingPiece = ChessPiece(PieceType::Bishop, white);
			blockingPos1 = Coordinate('g', 6);
			board.setPieceAt(&blockingPiece, &blockingPos1);

			Assert::IsFalse(board.fieldIsUnderAttack(&fieldToAttack, &white));
		}
		TEST_METHOD(searchForPieceTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			Coordinate pos = Coordinate('e', 8);
			ChessColor white = ChessColor::White;

			ChessPiece piece = ChessPiece(PieceType::Pawn, white);

			Assert::IsTrue(Coordinate() == board.searchForPiece(&piece));
			board.setPieceAt(&piece, &pos);
			Assert::IsTrue(pos == board.searchForPiece(&piece));

			board.clearBoard();

			pos = Coordinate('b', 3);
			ChessColor black = ChessColor::Black;

			piece = ChessPiece(PieceType::King, black);

			Assert::IsTrue(Coordinate() == board.searchForPiece(&piece));
			board.setPieceAt(&piece, &pos);
			Assert::IsTrue(pos == board.searchForPiece(&piece));
		}
		TEST_METHOD(isInCheckTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			//white king is under attack from black pawn
			ChessColor white = ChessColor::White;
			ChessColor black = ChessColor::Black;

			ChessPiece piece = ChessPiece(PieceType::King, white);
			Coordinate pos = Coordinate('c', 4);
			board.setPieceAt(&piece, &pos);

			ChessPiece enemyPiece = ChessPiece(PieceType::Pawn, ChessColor::Black);
			Coordinate enemyCoord = Coordinate('d', 5);
			board.setPieceAt(&enemyPiece, &enemyCoord);

			Assert::IsTrue(board.isInCheck(&white));
			board.clearPieceAt(&enemyCoord);

			//white king is not in check. queen is friendly
			ChessPiece friendlyPiece = ChessPiece(PieceType::Queen, ChessColor::White);
			Coordinate friendlyCoord = Coordinate('d', 4);
			board.setPieceAt(&friendlyPiece, &friendlyCoord);

			Assert::IsFalse(board.isInCheck(&white));
			board.clearPieceAt(&friendlyCoord);

			//black king is under attack from white pawn
			piece = ChessPiece(PieceType::King, black);
			pos = Coordinate('c', 4);
			board.setPieceAt(&piece, &pos);

			enemyPiece = ChessPiece(PieceType::Pawn, ChessColor::White);
			enemyCoord = Coordinate('d', 3);
			board.setPieceAt(&enemyPiece, &enemyCoord);

			Assert::IsTrue(board.isInCheck(&black));
			board.clearPieceAt(&enemyCoord);

			//black king is not in check. queen is friendly

			friendlyPiece = ChessPiece(PieceType::Queen, ChessColor::Black);
			friendlyCoord = Coordinate('d', 4);
			board.setPieceAt(&friendlyPiece, &friendlyCoord);

			Assert::IsFalse(board.isInCheck(&black));
		}
		TEST_METHOD(isInCheckWithMoveTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			//white king
			//is not under attack, because pawn moved past
			ChessColor white = ChessColor::White;
			ChessColor black = ChessColor::Black;

			ChessPiece piece = ChessPiece(PieceType::King, white);
			Coordinate pos = Coordinate('c', 4);
			board.setPieceAt(&piece, &pos);

			ChessPiece enemyPiece = ChessPiece(PieceType::Pawn, ChessColor::Black);
			Coordinate enemyCoord = Coordinate('d', 5);
			board.setPieceAt(&enemyPiece, &enemyCoord);
			Coordinate nextEnemyCoord = Coordinate('d', 6);
			Move enemyMove = Move(&enemyCoord, &nextEnemyCoord);

			Assert::IsFalse(board.isInCheck(&white, &enemyMove));
			board.clearPieceAt(&enemyCoord);

			//is under attack, because knight moved in
			enemyPiece = ChessPiece(PieceType::Knight, ChessColor::Black);
			enemyCoord = Coordinate('g', 4);
			board.setPieceAt(&enemyPiece, &enemyCoord);
			nextEnemyCoord = Coordinate('e', 3);
			enemyMove = Move(&enemyCoord, &nextEnemyCoord);

			Assert::IsTrue(board.isInCheck(&white, &enemyMove));
			board.clearBoard();

			//is under attack because en passant moved two blocked pieces away and opend the way for the enemy rook
			piece = ChessPiece(PieceType::King, black);
			pos = Coordinate('a', 4);
			board.setPieceAt(&piece, &pos);

			ChessPiece friendlyPiece = ChessPiece(PieceType::Pawn, ChessColor::Black);
			Coordinate friendlyCoord = Coordinate('b', 4);
			board.setPieceAt(&friendlyPiece, &friendlyCoord);

			enemyPiece = ChessPiece(PieceType::Rook, ChessColor::White);
			enemyCoord = Coordinate('h', 4);
			board.setPieceAt(&enemyPiece, &enemyCoord);

			ChessPiece enemyPiece2 = ChessPiece(PieceType::Pawn, ChessColor::White);
			Coordinate enemyCoord2 = Coordinate('c', 4);
			board.setPieceAt(&enemyPiece2, &enemyCoord2);

			Coordinate nextPosOfFriendlyPiece = Coordinate('c', 3);
			Move friendlyMove = Move(&friendlyCoord, &nextPosOfFriendlyPiece);

			Assert::IsTrue(board.isInCheck(&black, &friendlyMove));
		}
		TEST_METHOD(basicCastleVariablesAndFunctionsTest)
		{
			CastleType shortCastle = CastleType::Short;
			CastleType longCastle = CastleType::Long;

			Assert::AreEqual(0, (int)shortCastle);
			Assert::AreEqual(1, (int)longCastle);

			ChessColor white = ChessColor::White;
			ChessColor black = ChessColor::Black;

			Assert::AreEqual(0, (int)white);
			Assert::AreEqual(1, (int)black);

			ChessBoardTest board = ChessBoardTest();

			Assert::IsTrue(board.getCanCastle(white, shortCastle));
			Assert::IsTrue(board.getCanCastle(white, longCastle));
			Assert::IsTrue(board.getCanCastle(black, shortCastle));
			Assert::IsTrue(board.getCanCastle(black, longCastle));

			board.setCanCastle(white, shortCastle, false);
			board.setCanCastle(white, longCastle, false);
			board.setCanCastle(black, shortCastle, false);
			board.setCanCastle(black, longCastle, false);

			Assert::IsFalse(board.getCanCastle(white, shortCastle));
			Assert::IsFalse(board.getCanCastle(white, longCastle));
			Assert::IsFalse(board.getCanCastle(black, shortCastle));
			Assert::IsFalse(board.getCanCastle(black, longCastle));

			board.setCanCastle(white, shortCastle, true);
			Assert::IsTrue(board.getCanCastle(white, shortCastle));

			board.setCanCastleAll(false);
			Assert::IsFalse(board.getCanCastle(white, shortCastle));
		}
		TEST_METHOD(moveDisablesCastlingAbility)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			CastleType shortCastle = CastleType::Short;
			CastleType longCastle = CastleType::Long;
			ChessColor white = ChessColor::White;
			ChessColor black = ChessColor::Black;

			//cannot castle after clearing board
			Assert::IsFalse(board.getCanCastle(white, shortCastle));
			Assert::IsFalse(board.getCanCastle(white, longCastle));
			Assert::IsFalse(board.getCanCastle(black, shortCastle));
			Assert::IsFalse(board.getCanCastle(black, longCastle));

			board.setCanCastleAll(true);

			//move didnt affect the castling ability
			Move move = Move(&Coordinate('e', 2), &Coordinate('e', 3));
			board.updateCastlingAbility(&move);
			Assert::IsTrue(board.getCanCastle(white, shortCastle));
			Assert::IsTrue(board.getCanCastle(white, longCastle));
			Assert::IsTrue(board.getCanCastle(black, shortCastle));
			Assert::IsTrue(board.getCanCastle(black, longCastle));

			//move started on a1 - white cant castle long
			move = Move(&Coordinate('a', 1), &Coordinate('a', 2));
			board.updateCastlingAbility(&move);
			Assert::IsTrue(board.getCanCastle(white, shortCastle));
			Assert::IsFalse(board.getCanCastle(white, longCastle));
			Assert::IsTrue(board.getCanCastle(black, shortCastle));
			Assert::IsTrue(board.getCanCastle(black, longCastle));
			board.setCanCastleAll(true);

			//move ended on a1 - white cant castle long
			move = Move(&Coordinate('a', 2), &Coordinate('a', 1));
			board.updateCastlingAbility(&move);
			Assert::IsTrue(board.getCanCastle(white, shortCastle));
			Assert::IsFalse(board.getCanCastle(white, longCastle));
			Assert::IsTrue(board.getCanCastle(black, shortCastle));
			Assert::IsTrue(board.getCanCastle(black, longCastle));
			board.setCanCastleAll(true);

			//move started on h8 - black cant castle short
			move = Move(&Coordinate('h', 8), &Coordinate('h', 7));
			board.updateCastlingAbility(&move);
			Assert::IsTrue(board.getCanCastle(white, shortCastle));
			Assert::IsTrue(board.getCanCastle(white, longCastle));
			Assert::IsFalse(board.getCanCastle(black, shortCastle));
			Assert::IsTrue(board.getCanCastle(black, longCastle));
			board.setCanCastleAll(true);

			//move ended on e8 - black cant castle on both sides
			move = Move(&Coordinate('e', 7), &Coordinate('e', 8));
			board.updateCastlingAbility(&move);
			Assert::IsTrue(board.getCanCastle(white, shortCastle));
			Assert::IsTrue(board.getCanCastle(white, longCastle));
			Assert::IsFalse(board.getCanCastle(black, shortCastle));
			Assert::IsFalse(board.getCanCastle(black, longCastle));
		}
		TEST_METHOD(boardCastlingTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			CastleType shortCastle = CastleType::Short;
			CastleType longCastle = CastleType::Long;
			ChessColor white = ChessColor::White;
			ChessColor black = ChessColor::Black;
			board.setCanCastleAll(true);

			//white king castling with free space
			ChessPiece wk = ChessPiece(PieceType::King, white);
			Coordinate whiteKingPos = Coordinate('e', 1);
			board.setPieceAt(&wk, &whiteKingPos);

			Move expectedShortMoveWhite = Move(&whiteKingPos, &Coordinate('g', 1));
			Move expectedLongMoveWhite = Move(&whiteKingPos, &Coordinate('c', 1));

			std::vector<Move*> moves = board.getAllMovesOfPiece(&wk, &whiteKingPos);
			Assert::AreEqual(7, (int)moves.size());
			Assert::IsTrue(containsMove(moves, &expectedShortMoveWhite));
			Assert::IsTrue(containsMove(moves, &expectedLongMoveWhite));

			board.setCanCastle(white, shortCastle, false);
			moves = board.getAllMovesOfPiece(&wk, &whiteKingPos);
			Assert::AreEqual(6, (int)moves.size());
			Assert::IsFalse(containsMove(moves, &expectedShortMoveWhite));
			Assert::IsTrue(containsMove(moves, &expectedLongMoveWhite));

			board.setCanCastle(white, longCastle, false);
			moves = board.getAllMovesOfPiece(&wk, &whiteKingPos);
			Assert::AreEqual(5, (int)board.getAllMovesOfPiece(&wk, &whiteKingPos).size());
			Assert::IsFalse(containsMove(moves, &expectedShortMoveWhite));
			Assert::IsFalse(containsMove(moves, &expectedLongMoveWhite));

			//black king castling with free space
			ChessPiece bk = ChessPiece(PieceType::King, black);
			Coordinate blackKingPos = Coordinate('e', 8);
			board.setPieceAt(&bk, &blackKingPos);

			Move expectedShortMoveBlack = Move(&blackKingPos, &Coordinate('g', 8));
			Move expectedLongMoveBlack = Move(&blackKingPos, &Coordinate('c', 8));

			moves = board.getAllMovesOfPiece(&bk, &blackKingPos);
			Assert::AreEqual(7, (int)moves.size());
			Assert::IsTrue(containsMove(moves, &expectedShortMoveBlack));
			Assert::IsTrue(containsMove(moves, &expectedLongMoveBlack));

			board.setCanCastle(black, shortCastle, false);
			moves = board.getAllMovesOfPiece(&bk, &blackKingPos);
			Assert::AreEqual(6, (int)moves.size());
			Assert::IsFalse(containsMove(moves, &expectedShortMoveBlack));
			Assert::IsTrue(containsMove(moves, &expectedLongMoveBlack));

			board.setCanCastle(black, longCastle, false);
			moves = board.getAllMovesOfPiece(&bk, &blackKingPos);
			Assert::AreEqual(5, (int)moves.size());
			Assert::IsFalse(containsMove(moves, &expectedShortMoveBlack));
			Assert::IsFalse(containsMove(moves, &expectedLongMoveBlack));

			//now it is not relevant if the king or rook is moved
			board.setCanCastleAll(true);

			//white some piece stands in the way
			ChessPiece friendlyBlockingPiece = ChessPiece(PieceType::Bishop, white);
			Coordinate friendlyBlockingPiecePos = Coordinate('g', 1);
			board.setPieceAt(&friendlyBlockingPiece, &friendlyBlockingPiecePos);

			moves = board.getAllMovesOfPiece(&wk, &whiteKingPos);
			Assert::AreEqual(6, (int)moves.size());
			Assert::IsFalse(containsMove(moves, &expectedShortMoveWhite));
			Assert::IsTrue(containsMove(moves, &expectedLongMoveWhite));
			board.clearPieceAt(&friendlyBlockingPiecePos);

			//white cant castle long - someone attacks the final pos
			ChessPiece br = ChessPiece(PieceType::Rook, black);
			Coordinate blackRookPos = Coordinate('c', 4);
			board.setPieceAt(&br, &blackRookPos);

			moves = board.getAllMovesOfPiece(&wk, &whiteKingPos);
			Assert::AreEqual(6, (int)moves.size());
			Assert::IsTrue(containsMove(moves, &expectedShortMoveWhite));
			Assert::IsFalse(containsMove(moves, &expectedLongMoveWhite));
			board.clearPieceAt(&blackRookPos);

			//black some piece stands in the way
			ChessPiece friendlyBlockingPiece2 = ChessPiece(PieceType::Bishop, black);
			Coordinate friendlyBlockingPiecePos2 = Coordinate('g', 8);
			board.setPieceAt(&friendlyBlockingPiece2, &friendlyBlockingPiecePos2);

			moves = board.getAllMovesOfPiece(&bk, &blackKingPos);
			Assert::AreEqual(6, (int)moves.size());
			Assert::IsFalse(containsMove(moves, &expectedShortMoveBlack));
			Assert::IsTrue(containsMove(moves, &expectedLongMoveBlack));
			board.clearPieceAt(&friendlyBlockingPiecePos2);

			//black cant castle long - someone attacks the way
			ChessPiece wr = ChessPiece(PieceType::Rook, white);
			Coordinate whiteRookPos = Coordinate('d', 7);
			board.setPieceAt(&wr, &whiteRookPos);

			moves = board.getAllMovesOfPiece(&bk, &blackKingPos);
			Assert::AreEqual(6, (int)moves.size());
			Assert::IsTrue(containsMove(moves, &expectedShortMoveBlack));
			Assert::IsFalse(containsMove(moves, &expectedLongMoveBlack));
			board.clearPieceAt(&whiteRookPos);

			//black king is under attack - can do 5 moves, because this method
			//doesnt check for legal moves
			//it still rules out all castling moves, since you cannot castle out of a check

			whiteRookPos = Coordinate('e', 6);
			board.setPieceAt(&wr, &whiteRookPos);

			moves = board.getAllMovesOfPiece(&bk, &blackKingPos);
			Assert::AreEqual(5, (int)moves.size());
			Assert::IsFalse(containsMove(moves, &expectedShortMoveBlack));
			Assert::IsFalse(containsMove(moves, &expectedLongMoveBlack));
			board.clearPieceAt(&whiteRookPos);
		}
		TEST_METHOD(getAllMovesTest)
		{
			ChessBoardTest board = ChessBoardTest();

			ChessColor white = ChessColor::White;
			ChessColor black = ChessColor::Black;

			Assert::AreEqual(20, (int)board.getAllMoves(&white).size());
			Assert::AreEqual(20, (int)board.getAllMoves(&black).size());

			Coordinate coordToClear = Coordinate('f', 1);
			board.clearPieceAt(&coordToClear);
			coordToClear = Coordinate('g', 1);
			board.clearPieceAt(&coordToClear);

			//removing the light white bishop and the g-knight
			//now king can castle and move one move rook can move two moves
			//but the knight is not there anymore and thus cannot move 
			Assert::AreEqual(22, (int)board.getAllMoves(&white).size());
			
			coordToClear = Coordinate('b', 1);
			board.clearPieceAt(&coordToClear);
			coordToClear = Coordinate('c', 1);
			board.clearPieceAt(&coordToClear);
			
			Assert::AreEqual(24, (int)board.getAllMoves(&white).size());
		}
		TEST_METHOD(executeMoveTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			//Pawn promotion
			MovePawnPromotion pm = MovePawnPromotion(&Coordinate('a', 2), &Coordinate('a', 1), PieceType::Queen);

			board.executeMove(&pm);
			
			Assert::IsTrue(PieceType::Queen == board.getAtPosition(&Coordinate('a', 1)).getType());
			
			board.clearBoard();
			
			//king castling
			ChessColor white = ChessColor::White;
			ChessColor black = ChessColor::Black;
			
			ChessPiece bk = ChessPiece(PieceType::King, black);
			ChessPiece br = ChessPiece(PieceType::Rook, black);

			board.setPieceAt(&bk, &Coordinate('e', 8));
			board.setPieceAt(&br, &Coordinate('a', 8));

			Move secondMove = Move(&Coordinate('a', 8),&Coordinate('d', 8));
			MoveCastle cm = MoveCastle(&Coordinate('e', 8), &Coordinate('c', 8), secondMove);

			board.executeMove(&cm);
			
			Assert::IsTrue(PieceType::King == board.getAtPosition(&Coordinate('c', 8)).getType());
			Assert::IsTrue(PieceType::Rook == board.getAtPosition(&Coordinate('d', 8)).getType());

			board.clearBoard();
			//en passant executing
			ChessPiece wp = ChessPiece(PieceType::Pawn, white);
			ChessPiece bp = ChessPiece(PieceType::Pawn, black);
			
			board.setPieceAt(&wp, &Coordinate('d', 5));
			board.setPieceAt(&bp, &Coordinate('e', 5));
			
			MoveEnPassant ep = MoveEnPassant(&Coordinate('d', 5), &Coordinate('e', 6), Coordinate('e', 5));

			board.executeMove(&ep);

			Assert::IsTrue(wp == board.getAtPosition(&Coordinate('e', 6)));
			Assert::IsTrue(ChessPiece() == board.getAtPosition(&Coordinate('e', 5)));
			Assert::IsTrue(ChessPiece() == board.getAtPosition(&Coordinate('d', 5)));

			board.clearBoard();
		}
		TEST_METHOD(cannotExecuteMoveIfInCheckAfterTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			ChessPiece wk = ChessPiece(PieceType::King, ChessColor::White);
			ChessPiece bq = ChessPiece(PieceType::Queen, ChessColor::Black);

			board.setPieceAt(&wk, &Coordinate('a', 1));
			board.setPieceAt(&bq, &Coordinate('a', 8));
			
			Move move = Move(&Coordinate('a', 1), &Coordinate('b', 1));

			ChessColor white = ChessColor::White;

			Assert::IsFalse(board.isInCheck(&white, &move));
		}
	};
}