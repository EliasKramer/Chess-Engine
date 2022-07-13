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

void ChessBoardTest::setLastMove(Move* move)
{
	ChessBoard::setLastMove(move);
}

Move ChessBoardTest::getLastMove()
{
	return ChessBoard::getLastMove();
}

std::list<Move> ChessBoardTest::getAllMovesInDirection(Coordinate* start, ChessColor* color, short fileAddingValue, short rankAddingValue)
{
	return ChessBoard::getAllMovesInDirection(start, color,fileAddingValue,rankAddingValue);
}

std::list<Move> ChessBoardTest::getAllMovesOfPiece(ChessPiece* piece, Coordinate* coord)
{
	return ChessBoard::getAllMovesOfPiece(piece, coord);
}
RayCastResult* ChessBoardTest::executeRayCast(RayCastOptions* options)
{
	return ChessBoard::executeRayCast(options);
}
/*
bool ChessBoardTest::fieldGetsAttackedByEnemy(Coordinate* coord, ChessColor* color)
{
	return ChessBoard::fieldGetsAttackedByEnemy(coord, color);
}*/
