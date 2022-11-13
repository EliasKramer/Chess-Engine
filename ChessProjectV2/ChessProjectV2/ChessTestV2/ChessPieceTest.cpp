#include "CppUnitTest.h"
#include "../ChessProjectV2/BitBoard.h"
#include "../ChessProjectV2/ChessBoard.h"
#include "../ChessProjectV2/DataAndTypes.h"
#include "../ChessProjectV2/ChessBoardTest.h"
#include "../ChessProjectV2/ChessPiece.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PieceTest
{
	TEST_CLASS(PieceTest)
	{
	public:

		TEST_METHOD(constructorTest)
		{
			ChessPiece whitePawn(white, pawn);
			ChessPiece blackPawn(black, pawn);
			ChessPiece whiteKnight(white, knight);
			ChessPiece blackKnight(black, knight);
			ChessPiece whiteBishop(white, bishop);
			ChessPiece blackBishop(black, bishop);
			ChessPiece whiteRook(white, rook);
			ChessPiece blackRook(black, rook);
			ChessPiece whiteQueen(white, queen);
			ChessPiece blackQueen(black, queen);
			ChessPiece whiteKing(white, king);
			ChessPiece blackKing(black, king);
			
			Assert::IsTrue(white == whitePawn.get_color());
			Assert::IsTrue(pawn == whitePawn.get_type());
			Assert::IsTrue(black == blackPawn.get_color());
			Assert::IsTrue(pawn == blackPawn.get_type());
			
			Assert::IsTrue(white == whiteKnight.get_color());
			Assert::IsTrue(knight == whiteKnight.get_type());
			Assert::IsTrue(black == blackKnight.get_color());
			Assert::IsTrue(knight == blackKnight.get_type());
			
			Assert::IsTrue(white == whiteBishop.get_color());
			Assert::IsTrue(bishop == whiteBishop.get_type());
			Assert::IsTrue(black == blackBishop.get_color());
			Assert::IsTrue(bishop == blackBishop.get_type());
			
			Assert::IsTrue(white == whiteRook.get_color());
			Assert::IsTrue(rook == whiteRook.get_type());
			Assert::IsTrue(black == blackRook.get_color());
			Assert::IsTrue(rook == blackRook.get_type());
			
			Assert::IsTrue(white == whiteQueen.get_color());
			Assert::IsTrue(queen == whiteQueen.get_type());
			Assert::IsTrue(black == blackQueen.get_color());
			Assert::IsTrue(queen == blackQueen.get_type());
			
			Assert::IsTrue(white == whiteKing.get_color());
			Assert::IsTrue(king == whiteKing.get_type());
			Assert::IsTrue(black == blackKing.get_color());
			Assert::IsTrue(king == blackKing.get_type());		
		}
		TEST_METHOD(equalTest)
		{
			ChessPiece whitePawn(white, pawn);
			
			Assert::IsTrue(whitePawn == ChessPiece(white, pawn));
			Assert::IsTrue(ChessPiece(white, pawn) == whitePawn);
			
			Assert::IsFalse(ChessPiece(black, pawn) == whitePawn);
			Assert::IsFalse(ChessPiece(white, rook) == whitePawn);
			
			Assert::IsFalse(whitePawn != ChessPiece(white, pawn));
			Assert::IsFalse(ChessPiece(white, pawn) != whitePawn);

			Assert::IsTrue(ChessPiece(black, pawn) != whitePawn);
			Assert::IsTrue(ChessPiece(white, rook) != whitePawn);
		}
		TEST_METHOD(fenCreation)
		{
			Assert::IsTrue(ChessPiece(black, queen) == ChessPiece('q'));
			Assert::IsTrue(ChessPiece(white, queen) == ChessPiece('Q'));

			Assert::IsTrue(ChessPiece(black, king) == ChessPiece('k'));
			Assert::IsTrue(ChessPiece(white, king) == ChessPiece('K'));
			
			Assert::IsTrue(ChessPiece(black, rook) == ChessPiece('r'));
			Assert::IsTrue(ChessPiece(white, rook) == ChessPiece('R'));

			Assert::IsTrue(ChessPiece(black, bishop) == ChessPiece('b'));
			Assert::IsTrue(ChessPiece(white, bishop) == ChessPiece('B'));

			Assert::IsTrue(ChessPiece(black, knight) == ChessPiece('n'));
			Assert::IsTrue(ChessPiece(white, knight) == ChessPiece('N'));
			
			Assert::IsTrue(ChessPiece(black, pawn) == ChessPiece('p'));
			Assert::IsTrue(ChessPiece(white, pawn) == ChessPiece('P'));
		}
	};
}