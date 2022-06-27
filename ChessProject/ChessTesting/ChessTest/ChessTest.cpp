#include "pch.h"
#include "CppUnitTest.h"
#include "../../ChessProject/MetaData.h"
#include "../../ChessProject/ChessPiece.h"
#include "../../ChessProject/ChessBoard.h"
#include "../../ChessProject/ChessBoardTest.h"
#include "../../ChessProject/Move.h"
#include "../../ChessProject/Coordinate.h"
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

			Assert::AreEqual((int)PieceType::Pawn,(int)*wp.getType());
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
			
			Coordinate arrA1 = Coordinate((unsigned short)0, (unsigned short)0);
			Coordinate arrH8 = Coordinate((unsigned short)7, (unsigned short)7);
			
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
			for(char file = 'a'; file <= 'h'; file++)
			{
				Assert::IsTrue(
					*(board.getAtPosition(&Coordinate(file, 2))) ==
					ChessPiece(PieceType::Pawn, ChessColor::White));
				for(int rank = 3; rank <= 6; rank++)
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
			for(char file = 'a'; file <= 'h'; file++)
			{
				for(int rank = 1; rank <= 8; rank++)
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
		TEST_METHOD(chessBoardLegalMoveValidInputsTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			//invalid, because move coords are not valid
			//last coord not valid
			Move invalidMove = Move(&Coordinate('a',1),&Coordinate());
			Assert::IsFalse(board.moveIsLegal(&invalidMove));
			//first coord not valid
			invalidMove = Move(&Coordinate(), &Coordinate('b', 5));
			Assert::IsFalse(board.moveIsLegal(&invalidMove));
			//start and dest are same
			invalidMove = Move(&Coordinate('a', 1), &Coordinate('a', 1));
			Assert::IsFalse(board.moveIsLegal(&invalidMove));
			//no coord is valid
			invalidMove = Move(&Coordinate(), &Coordinate());
			Assert::IsFalse(board.moveIsLegal(&invalidMove));
			
			//no piece at that field
			Coordinate piecePos = Coordinate('a', 2);
			Move testMove = Move(&piecePos, &Coordinate('a', 3));
			Assert::IsFalse(board.moveIsLegal(&testMove));
			
			//now we set a piece at that coord. the move should be legal
			board.setPieceAt(&ChessPiece(PieceType::Pawn, ChessColor::White), &piecePos);
			Assert::IsTrue(board.moveIsLegal(&testMove));

			//not his turn - should be false
			ChessColor white = ChessColor::White;
			ChessColor black = ChessColor::Black;
			
			board.setTurnColor(&black);
			Assert::IsFalse(board.moveIsLegal(&testMove));

			//his turn again - should be true like before
			board.setTurnColor(&white);
			Assert::IsTrue(board.moveIsLegal(&testMove));
		}
		TEST_METHOD(chessBoardLegalRookMoveTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();
			
			PieceType pieceType = PieceType::Rook;
			
			//valid moves
			Move move = Move(&Coordinate('a', 1), &Coordinate('a', 2));
			Assert::IsTrue(board.typeMoveLegal(&pieceType, &move));
			move = Move(&Coordinate('a', 1), &Coordinate('a', 8));
			Assert::IsTrue(board.typeMoveLegal(&pieceType, &move));
			move = Move(&Coordinate('a', 1), &Coordinate('h', 1));
			Assert::IsTrue(board.typeMoveLegal(&pieceType, &move));
			move = Move(&Coordinate('h', 1), &Coordinate('h', 8));
			Assert::IsTrue(board.typeMoveLegal(&pieceType, &move));
			move = Move(&Coordinate('d', 1), &Coordinate('d', 6));
			Assert::IsTrue(board.typeMoveLegal(&pieceType, &move));
			
			//invalid moves
			move = Move(&Coordinate('a', 1), &Coordinate('b', 2));
			Assert::IsFalse(board.typeMoveLegal(&pieceType, &move));
			move = Move(&Coordinate('a', 1), &Coordinate('c', 7));
			Assert::IsFalse(board.typeMoveLegal(&pieceType, &move));
			move = Move(&Coordinate('b', 1), &Coordinate('a', 2));
			Assert::IsFalse(board.typeMoveLegal(&pieceType, &move));
			move = Move(&Coordinate('a', 1), &Coordinate('h', 8));
			Assert::IsFalse(board.typeMoveLegal(&pieceType, &move));
		}
		TEST_METHOD(chessBoardLegalBishopMoveTest)
		{
			ChessBoardTest board = ChessBoardTest();
			board.clearBoard();

			PieceType pieceType = PieceType::Bishop;

			//valid moves
			Move move = Move(&Coordinate('a', 1), &Coordinate('b', 2));
			Assert::IsTrue(board.typeMoveLegal(&pieceType, &move));
			move = Move(&Coordinate('a', 1), &Coordinate('c', 3));
			Assert::IsTrue(board.typeMoveLegal(&pieceType, &move));
			move = Move(&Coordinate('e', 5), &Coordinate('h', 2));
			Assert::IsTrue(board.typeMoveLegal(&pieceType, &move));
			move = Move(&Coordinate('d', 4), &Coordinate('b', 6));
			Assert::IsTrue(board.typeMoveLegal(&pieceType, &move));
			move = Move(&Coordinate('d', 5), &Coordinate('b', 3));
			Assert::IsTrue(board.typeMoveLegal(&pieceType, &move));
			move = Move(&Coordinate('a', 1), &Coordinate('h', 8));
			Assert::IsTrue(board.typeMoveLegal(&pieceType, &move));
			move = Move(&Coordinate('h', 8), &Coordinate('a', 1));
			Assert::IsTrue(board.typeMoveLegal(&pieceType, &move));
			move = Move(&Coordinate('a', 8), &Coordinate('h', 1));
			Assert::IsTrue(board.typeMoveLegal(&pieceType, &move));
			move = Move(&Coordinate('h', 1), &Coordinate('a', 8));
			Assert::IsTrue(board.typeMoveLegal(&pieceType, &move));

			//invalid moves
			move = Move(&Coordinate('a', 1), &Coordinate('a', 2));
			Assert::IsFalse(board.typeMoveLegal(&pieceType, &move));
			move = Move(&Coordinate('a', 1), &Coordinate('a', 8));
			Assert::IsFalse(board.typeMoveLegal(&pieceType, &move));
			move = Move(&Coordinate('a', 1), &Coordinate('h', 1));
			Assert::IsFalse(board.typeMoveLegal(&pieceType, &move));
			move = Move(&Coordinate('h', 1), &Coordinate('h', 8));
			Assert::IsFalse(board.typeMoveLegal(&pieceType, &move));
			move = Move(&Coordinate('d', 1), &Coordinate('d', 6));
			Assert::IsFalse(board.typeMoveLegal(&pieceType, &move));
		}
	};
}
