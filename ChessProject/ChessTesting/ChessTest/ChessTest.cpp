#include "pch.h"
#include "CppUnitTest.h"
#include <list>
#include "../../ChessProject/MetaData.h"
#include "../../ChessProject/ChessPiece.h"
#include "../../ChessProject/ChessBoard.h"
#include "../../ChessProject/ChessBoardTest.h"
#include "../../ChessProject/Move.h"
#include "../../ChessProject/Coordinate.h"
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

			Assert::AreEqual((int)PieceType::Pawn, (int)*wp.getType());
			Assert::AreEqual((int)PieceType::Pawn, (int)*bp.getType());
			Assert::AreEqual((int)PieceType::Rook, (int)*wr.getType());
			Assert::AreEqual((int)PieceType::Rook, (int)*br.getType());
			Assert::AreEqual((int)PieceType::King, (int)*wk.getType());
			Assert::AreEqual((int)PieceType::King, (int)*bk.getType());
			Assert::AreEqual((int)PieceType::Knight, (int)*wn.getType());
			Assert::AreEqual((int)PieceType::Knight, (int)*bn.getType());
			Assert::AreEqual((int)PieceType::Bishop, (int)*wb.getType());
			Assert::AreEqual((int)PieceType::Bishop, (int)*bb.getType());
			Assert::AreEqual((int)PieceType::Queen, (int)*wq.getType());
			Assert::AreEqual((int)PieceType::Queen, (int)*bq.getType());

			Assert::AreEqual((int)ChessColor::White, (int)*wp.getColor());
			Assert::AreEqual((int)ChessColor::Black, (int)*bp.getColor());
			Assert::AreEqual((int)ChessColor::White, (int)*wr.getColor());
			Assert::AreEqual((int)ChessColor::Black, (int)*br.getColor());
			Assert::AreEqual((int)ChessColor::White, (int)*wk.getColor());
			Assert::AreEqual((int)ChessColor::Black, (int)*bk.getColor());
			Assert::AreEqual((int)ChessColor::White, (int)*wn.getColor());
			Assert::AreEqual((int)ChessColor::Black, (int)*bn.getColor());
			Assert::AreEqual((int)ChessColor::White, (int)*wb.getColor());
			Assert::AreEqual((int)ChessColor::Black, (int)*bb.getColor());
			Assert::AreEqual((int)ChessColor::White, (int)*wq.getColor());
			Assert::AreEqual((int)ChessColor::Black, (int)*bq.getColor());
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
			Assert::AreEqual((int)ChessColor::NoColor, (int)*p.getColor());
			Assert::AreEqual((int)PieceType::NoType, (int)*p.getType());
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
			ChessPiece* gottenPiece = board.getAtPosition(&Coordinate('a', 1));
			Assert::IsTrue(wr == *gottenPiece);
			gottenPiece = board.getAtPosition(&Coordinate('a', 2));
			Assert::IsFalse(wr == *gottenPiece);

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
			Assert::IsFalse(defaultConstructor.getDestination()->isValid());
			Assert::IsFalse(defaultConstructor.getStart()->isValid());
			Assert::IsFalse(defaultConstructor.isValid());

			Move move = Move(
				&Coordinate('a', 1),
				&Coordinate('b', 2));

			Assert::IsTrue(move.getStart()->isValid());
			Assert::IsTrue(move.getDestination()->isValid());
			Assert::IsFalse(*(move.getDestination()) == *(move.getStart()));

			Assert::IsTrue(Coordinate('a', 1) == *(move.getStart()));
			Assert::IsTrue(Coordinate('b', 2) == *(move.getDestination()));

			Assert::IsTrue(move.isValid());
		}
		TEST_METHOD(defaultBoardSetupTest)
		{
			ChessBoardTest board = ChessBoardTest();
			Assert::IsTrue(
				*(board.getAtPosition(&Coordinate('a', 1))) ==
				ChessPiece(PieceType::Rook, ChessColor::White));
			Assert::IsTrue(
				*(board.getAtPosition(&Coordinate('b', 1))) ==
				ChessPiece(PieceType::Knight, ChessColor::White));
			Assert::IsTrue(
				*(board.getAtPosition(&Coordinate('c', 1))) ==
				ChessPiece(PieceType::Bishop, ChessColor::White));
			Assert::IsTrue(
				*(board.getAtPosition(&Coordinate('d', 1))) ==
				ChessPiece(PieceType::Queen, ChessColor::White));
			Assert::IsTrue(
				*(board.getAtPosition(&Coordinate('e', 1))) ==
				ChessPiece(PieceType::King, ChessColor::White));
			Assert::IsTrue(
				*(board.getAtPosition(&Coordinate('f', 1))) ==
				ChessPiece(PieceType::Bishop, ChessColor::White));
			Assert::IsTrue(
				*(board.getAtPosition(&Coordinate('g', 1))) ==
				ChessPiece(PieceType::Knight, ChessColor::White));
			Assert::IsTrue(
				*(board.getAtPosition(&Coordinate('h', 1))) ==
				ChessPiece(PieceType::Rook, ChessColor::White));
			for (char file = 'a'; file <= 'h'; file++)
			{
				Assert::IsTrue(
					*(board.getAtPosition(&Coordinate(file, 2))) ==
					ChessPiece(PieceType::Pawn, ChessColor::White));
				for (int rank = 3; rank <= 6; rank++)
				{
					Assert::IsFalse(board.getAtPosition(&Coordinate(file, rank))->isValid());
					Assert::IsTrue(
						*(board.getAtPosition(&Coordinate(file, rank))) ==
						ChessPiece(PieceType::NoType, ChessColor::NoColor));
				}
				Assert::IsTrue(
					*(board.getAtPosition(&Coordinate(file, 7))) ==
					ChessPiece(PieceType::Pawn, ChessColor::Black));
			}
			Assert::IsTrue(
				*(board.getAtPosition(&Coordinate('a', 8))) ==
				ChessPiece(PieceType::Rook, ChessColor::Black));
			Assert::IsTrue(
				*(board.getAtPosition(&Coordinate('b', 8))) ==
				ChessPiece(PieceType::Knight, ChessColor::Black));
			Assert::IsTrue(
				*(board.getAtPosition(&Coordinate('c', 8))) ==
				ChessPiece(PieceType::Bishop, ChessColor::Black));
			Assert::IsTrue(
				*(board.getAtPosition(&Coordinate('d', 8))) ==
				ChessPiece(PieceType::Queen, ChessColor::Black));
			Assert::IsTrue(
				*(board.getAtPosition(&Coordinate('e', 8))) ==
				ChessPiece(PieceType::King, ChessColor::Black));
			Assert::IsTrue(
				*(board.getAtPosition(&Coordinate('f', 8))) ==
				ChessPiece(PieceType::Bishop, ChessColor::Black));
			Assert::IsTrue(
				*(board.getAtPosition(&Coordinate('g', 8))) ==
				ChessPiece(PieceType::Knight, ChessColor::Black));
			Assert::IsTrue(
				*(board.getAtPosition(&Coordinate('h', 8))) ==
				ChessPiece(PieceType::Rook, ChessColor::Black));
		}
		TEST_METHOD(chessboardExecuteMoveTest)
		{
			//do move is doing the move and just checks if it is possible.
			//not if it is legal.
			ChessBoardTest board = ChessBoardTest();

			Coordinate start = Coordinate('a', 1);
			Coordinate dest = Coordinate('b', 2);
			Coordinate invalid = Coordinate();

			Move move = Move(&start, &dest);
			Assert::IsTrue(board.executeMove(&move));

			move = Move(&start, &start);
			Assert::IsFalse(board.executeMove(&move));

			move = Move(&invalid, &invalid);
			Assert::IsFalse(board.executeMove(&move));

			move = Move(&start, &invalid);
			Assert::IsFalse(board.executeMove(&move));

			move = Move(&invalid, &dest);
			Assert::IsFalse(board.executeMove(&move));
		}
		TEST_METHOD(chessBoardClearTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();
			for (char file = 'a'; file <= 'h'; file++)
			{
				for (int rank = 1; rank <= 8; rank++)
				{
					Assert::IsFalse(board.getAtPosition(&Coordinate(file, rank))->isValid());
					Assert::IsTrue(
						*(board.getAtPosition(&Coordinate(file, rank))) ==
						ChessPiece(PieceType::NoType, ChessColor::NoColor));
				}
			}
		}
		TEST_METHOD(chessBoardSetAndGetTurnColorTest)
		{
			ChessBoardTest board = ChessBoardTest();
			ChessColor white = ChessColor::White;
			ChessColor black = ChessColor::Black;

			Assert::IsTrue((int)*board.getTurnColor() == (int)ChessColor::White);
			board.setTurnColor(&black);
			Assert::IsTrue((int)*board.getTurnColor() == (int)ChessColor::Black);
			board.setTurnColor(&white);
			Assert::IsTrue((int)*board.getTurnColor() == (int)ChessColor::White);
			board.setTurnColor(&white);
			Assert::IsTrue((int)*board.getTurnColor() == (int)ChessColor::White);
		}
		TEST_METHOD(boardGetAllMovesNoMovesAvailible)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();
			std::list<Move> possibleMoves = board.getAllMoves();

			Assert::AreEqual((int)possibleMoves.size(), 0);
		}
		TEST_METHOD(boardGetMovesInDirectionWithoutObstaclesTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			Coordinate start = Coordinate('a', 1);
			ChessColor white = ChessColor::White;

			std::list<Move> moves =
				board.getAllMovesInDirection(&start, &white, 1, 0);
			Assert::AreEqual(7, (int)moves.size());
			char file = 'b';
			for (
				std::list<Move>::iterator it = moves.begin();
				it != moves.end();
				++it) {
				Assert::IsTrue(it->isValid());

				Assert::IsTrue(Coordinate(file, (unsigned short)1) == *it->getDestination());
				Assert::IsTrue(Coordinate('a', 1) == *it->getStart());
				file++;
			}

			moves =
				board.getAllMovesInDirection(&start, &white, -1, 0);
			Assert::AreEqual(0, (int)moves.size());

			moves =
				board.getAllMovesInDirection(&start, &white, 0, -1);
			Assert::AreEqual(0, (int)moves.size());

			moves =
				board.getAllMovesInDirection(&start, &white, 0, 1);
			Assert::AreEqual(7, (int)moves.size());

			moves =
				board.getAllMovesInDirection(&start, &white, 1, 1);
			Assert::AreEqual(7, (int)moves.size());

			moves =
				board.getAllMovesInDirection(&start, &white, 1, -1);
			Assert::AreEqual(0, (int)moves.size());

			//check every direction in the middle of the field
			start = Coordinate('d', 5);

			//straigt lines
			moves =
				board.getAllMovesInDirection(&start, &white, 1, 0);
			Assert::AreEqual(4, (int)moves.size());

			moves =
				board.getAllMovesInDirection(&start, &white, -1, 0);
			Assert::AreEqual(3, (int)moves.size());

			moves =
				board.getAllMovesInDirection(&start, &white, 0, -1);
			Assert::AreEqual(4, (int)moves.size());

			moves =
				board.getAllMovesInDirection(&start, &white, 0, 1);
			Assert::AreEqual(3, (int)moves.size());

			//diagonal checks
			moves =
				board.getAllMovesInDirection(&start, &white, 1, 1);
			Assert::AreEqual(3, (int)moves.size());

			moves =
				board.getAllMovesInDirection(&start, &white, 1, -1);
			Assert::AreEqual(4, (int)moves.size());

			moves =
				board.getAllMovesInDirection(&start, &white, -1, 1);
			Assert::AreEqual(3, (int)moves.size());

			moves =
				board.getAllMovesInDirection(&start, &white, -1, -1);
			Assert::AreEqual(3, (int)moves.size());
		}
		TEST_METHOD(boardGetMovesInDirectionWithObstaclesTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			board.setPieceAt(&ChessPiece(
				PieceType::Rook, ChessColor::Black),
				&Coordinate('g', 4));

			Coordinate start = Coordinate('d', 4);
			ChessColor white = ChessColor::White;

			std::list<Move> moves =
				board.getAllMovesInDirection(&start, &white, 1, 0);
			Assert::AreEqual(3, (int)moves.size());

			board.setPieceAt(&ChessPiece(
				PieceType::Rook, ChessColor::White),
				&Coordinate('g', 4));
			moves =
				board.getAllMovesInDirection(&start, &white, 1, 0);
			Assert::AreEqual(2, (int)moves.size());
		}
		TEST_METHOD(boardGetSimpleMovementOfPiecesTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			Coordinate coord = Coordinate('a', 1);

			//test moves at a1
			std::list<Move> allMoves =
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
			std::list<Move> allMoves =
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
			std::list<Move> allMoves =
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
			std::list<Move> allMoves =
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

			std::list<Move> allMoves =
				board.getAllMovesOfPiece(&ChessPiece(
					PieceType::Pawn, ChessColor::White),
					&Coordinate('b', 5));
			Assert::AreEqual(2, (int)allMoves.size());
			Assert::IsTrue(
				containsMove(allMoves,
					Move(
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
					Move(
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
		}
		TEST_METHOD(boardGetMovementOfKingTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			//king is free to move
			std::list<Move> allMoves =
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
		TEST_METHOD(boardCastlingTest)
		{
		}
	};
}