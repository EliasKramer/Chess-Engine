#include "ChessBoardTest.h"

void ChessBoardTest::setPieceAt(ChessPiece* piece, Coordinate* coord)
{
    ChessBoard::setPieceAt(piece, coord);
}

void ChessBoardTest::clearBoard()
{
	for(int file = 0; file < BOARD_SIZE; file++)
	{
		for(int rank = 0; rank < BOARD_SIZE; rank++)
		{
			board[file][rank] = ChessPiece();
		}
	}
}

void ChessBoardTest::setTurnColor(ChessColor* color)
{
	isWhiteTurn = *color == ChessColor::White;
}

bool ChessBoardTest::executeMove(Move* givenMove)
{
    return ChessBoard::executeMove(givenMove);
}

bool ChessBoardTest::moveIsLegal(Move* givenMove)
{
    return ChessBoard::moveIsLegal(givenMove);
}

bool ChessBoardTest::pieceIsAlledToMoveInThisWay(ChessPiece* type, Move* givenMove)
{
	return ChessBoard::pieceIsAlledToMoveInThisWay(type,givenMove);
}