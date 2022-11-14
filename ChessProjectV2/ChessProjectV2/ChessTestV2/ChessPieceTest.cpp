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

		TEST_METHOD(piece_constructor_test)
		{
			ChessPiece white_pawn(white, pawn);
			ChessPiece black_pawn(black, pawn);
			ChessPiece white_knight(white, knight);
			ChessPiece black_knight(black, knight);
			ChessPiece white_bishop(white, bishop);
			ChessPiece black_bishop(black, bishop);
			ChessPiece white_rook(white, rook);
			ChessPiece black_rook(black, rook);
			ChessPiece white_queen(white, queen);
			ChessPiece black_queen(black, queen);
			ChessPiece white_king(white, king);
			ChessPiece black_king(black, king);
			
			Assert::IsTrue(white == white_pawn.get_color());
			Assert::IsTrue(pawn == white_pawn.get_type());
			Assert::IsTrue(black == black_pawn.get_color());
			Assert::IsTrue(pawn == black_pawn.get_type());
			
			Assert::IsTrue(white == white_knight.get_color());
			Assert::IsTrue(knight == white_knight.get_type());
			Assert::IsTrue(black == black_knight.get_color());
			Assert::IsTrue(knight == black_knight.get_type());
			
			Assert::IsTrue(white == white_bishop.get_color());
			Assert::IsTrue(bishop == white_bishop.get_type());
			Assert::IsTrue(black == black_bishop.get_color());
			Assert::IsTrue(bishop == black_bishop.get_type());
			
			Assert::IsTrue(white == white_rook.get_color());
			Assert::IsTrue(rook == white_rook.get_type());
			Assert::IsTrue(black == black_rook.get_color());
			Assert::IsTrue(rook == black_rook.get_type());
			
			Assert::IsTrue(white == white_queen.get_color());
			Assert::IsTrue(queen == white_queen.get_type());
			Assert::IsTrue(black == black_queen.get_color());
			Assert::IsTrue(queen == black_queen.get_type());
			
			Assert::IsTrue(white == white_king.get_color());
			Assert::IsTrue(king == white_king.get_type());
			Assert::IsTrue(black == black_king.get_color());
			Assert::IsTrue(king == black_king.get_type());		
		}
		TEST_METHOD(equal_piece_test)
		{
			ChessPiece white_pawn(white, pawn);
			
			Assert::IsTrue(white_pawn == ChessPiece(white, pawn));
			Assert::IsTrue(ChessPiece(white, pawn) == white_pawn);
			
			Assert::IsFalse(ChessPiece(black, pawn) == white_pawn);
			Assert::IsFalse(ChessPiece(white, rook) == white_pawn);
			
			Assert::IsFalse(white_pawn != ChessPiece(white, pawn));
			Assert::IsFalse(ChessPiece(white, pawn) != white_pawn);

			Assert::IsTrue(ChessPiece(black, pawn) != white_pawn);
			Assert::IsTrue(ChessPiece(white, rook) != white_pawn);
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