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
			ChessPiece whitePawn(White, Pawn);
			ChessPiece blackPawn(Black, Pawn);
			ChessPiece whiteKnight(White, Knight);
			ChessPiece blackKnight(Black, Knight);
			ChessPiece whiteBishop(White, Bishop);
			ChessPiece blackBishop(Black, Bishop);
			ChessPiece whiteRook(White, Rook);
			ChessPiece blackRook(Black, Rook);
			ChessPiece whiteQueen(White, Queen);
			ChessPiece blackQueen(Black, Queen);
			ChessPiece whiteKing(White, King);
			ChessPiece blackKing(Black, King);
			
			Assert::IsTrue(White == whitePawn.getColor());
			Assert::IsTrue(Pawn == whitePawn.getType());
			Assert::IsTrue(Black == blackPawn.getColor());
			Assert::IsTrue(Pawn == blackPawn.getType());
			
			Assert::IsTrue(White == whiteKnight.getColor());
			Assert::IsTrue(Knight == whiteKnight.getType());
			Assert::IsTrue(Black == blackKnight.getColor());
			Assert::IsTrue(Knight == blackKnight.getType());
			
			Assert::IsTrue(White == whiteBishop.getColor());
			Assert::IsTrue(Bishop == whiteBishop.getType());
			Assert::IsTrue(Black == blackBishop.getColor());
			Assert::IsTrue(Bishop == blackBishop.getType());
			
			Assert::IsTrue(White == whiteRook.getColor());
			Assert::IsTrue(Rook == whiteRook.getType());
			Assert::IsTrue(Black == blackRook.getColor());
			Assert::IsTrue(Rook == blackRook.getType());
			
			Assert::IsTrue(White == whiteQueen.getColor());
			Assert::IsTrue(Queen == whiteQueen.getType());
			Assert::IsTrue(Black == blackQueen.getColor());
			Assert::IsTrue(Queen == blackQueen.getType());
			
			Assert::IsTrue(White == whiteKing.getColor());
			Assert::IsTrue(King == whiteKing.getType());
			Assert::IsTrue(Black == blackKing.getColor());
			Assert::IsTrue(King == blackKing.getType());		
		}
		TEST_METHOD(equalTest)
		{
			ChessPiece whitePawn(White, Pawn);
			
			Assert::IsTrue(whitePawn == ChessPiece(White, Pawn));
			Assert::IsTrue(ChessPiece(White, Pawn) == whitePawn);
			
			Assert::IsFalse(ChessPiece(Black, Pawn) == whitePawn);
			Assert::IsFalse(ChessPiece(White, Rook) == whitePawn);
			
			Assert::IsFalse(whitePawn != ChessPiece(White, Pawn));
			Assert::IsFalse(ChessPiece(White, Pawn) != whitePawn);

			Assert::IsTrue(ChessPiece(Black, Pawn) != whitePawn);
			Assert::IsTrue(ChessPiece(White, Rook) != whitePawn);
		}
		TEST_METHOD(fenCreation)
		{
			Assert::IsTrue(ChessPiece(Black, Queen) == ChessPiece('q'));
			Assert::IsTrue(ChessPiece(White, Queen) == ChessPiece('Q'));

			Assert::IsTrue(ChessPiece(Black, King) == ChessPiece('k'));
			Assert::IsTrue(ChessPiece(White, King) == ChessPiece('K'));
			
			Assert::IsTrue(ChessPiece(Black, Rook) == ChessPiece('r'));
			Assert::IsTrue(ChessPiece(White, Rook) == ChessPiece('R'));

			Assert::IsTrue(ChessPiece(Black, Bishop) == ChessPiece('b'));
			Assert::IsTrue(ChessPiece(White, Bishop) == ChessPiece('B'));

			Assert::IsTrue(ChessPiece(Black, Knight) == ChessPiece('n'));
			Assert::IsTrue(ChessPiece(White, Knight) == ChessPiece('N'));
			
			Assert::IsTrue(ChessPiece(Black, Pawn) == ChessPiece('p'));
			Assert::IsTrue(ChessPiece(White, Pawn) == ChessPiece('P'));
			/*
			try {
				ChessPiece invalidPiece('a');
				Assert::Fail();
			}
			catch (std::exception e) {
				Assert::IsTrue(true);
			}*/
		}
	};
}