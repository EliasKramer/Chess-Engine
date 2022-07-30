#include "ChessBoardTest.h"

void ChessBoardTest::setPieceAt(ChessPiece piece, Coordinate coord)
{
	ChessBoard::setPieceAt(piece, coord);
}

void ChessBoardTest::clearPieceAt(Coordinate* coord)
{
	board[coord->getFileAsPosition()][coord->getRankAsPosition()] = ChessPiece();
}

void ChessBoardTest::clearBoard()
{
	for (int file = 0; file < BOARD_SIZE; file++)
	{
		for (int rank = 0; rank < BOARD_SIZE; rank++)
		{
			board[file][rank] = ChessPiece();
		}
	}
	//if you clear a board you cannot castle anymore
	for (int color = 0; color < 2; color++)
	{
		for (int direction = 0; direction < 2; direction++)
		{
			canCastle[color][direction] = false;
		}
	}
}

void ChessBoardTest::setLastMove(Move* move)
{
	ChessBoard::setLastMove(move);
}

Move ChessBoardTest::getLastMove()
{
	return ChessBoard::getLastMove();
}

std::vector<Move*> ChessBoardTest::getAllMovesOfPiece(ChessPiece piece, Coordinate coord)
{
	return ChessBoard::getAllMovesOfPiece(piece, coord);
}
RayCastResult ChessBoardTest::executeSingleRayCast(RayCastOptions& options, short fileAddingVal, short rankAddingVal)
{
	return ChessBoard::executeSingleRayCast(options, fileAddingVal, rankAddingVal);
}
ChessPiece ChessBoardTest::getAtPostitionWithMoveDone(Coordinate* coord, Move* move)
{
	return ChessBoard::getAtPostitionWithMoveDone(coord, move);
}
RayCastResult ChessBoardTest::executeRayCast(
	PieceType type,
	RayCastOptions& options,
	bool shouldCalculateIfItIsUnderAttack)
{
	return ChessBoard::executeRayCast(type, options, shouldCalculateIfItIsUnderAttack);
}

bool ChessBoardTest::fieldIsUnderAttack(Coordinate coord, ChessColor color)
{
	return ChessBoard::fieldIsUnderAttack(coord, color);
}

Coordinate ChessBoardTest::searchForPiece(ChessPiece piece)
{
	return ChessBoard::searchForPiece(piece);
}

bool ChessBoardTest::isInCheck(ChessColor col)
{
	return ChessBoard::isInCheck(col);
}

bool ChessBoardTest::isInCheck(ChessColor col, Move move)
{
	return ChessBoard::isInCheck(col, move);
}

void ChessBoardTest::setCanCastle(ChessColor col, CastleType cType, bool value)
{
	ChessBoard::setCanCastle(col, cType, value);
}

bool ChessBoardTest::getCanCastle(ChessColor col, CastleType cType)
{
	return ChessBoard::getCanCastle(col, cType);
}

void ChessBoardTest::setCanCastleAll(bool value)
{
	for (int color = 0; color < 2; color++)
	{
		for (int direction = 0; direction < 2; direction++)
		{
			canCastle[color][direction] = value;
		}
	}
}

void ChessBoardTest::updateCastlingAbility(Move move)
{
	ChessBoard::updateCastlingAbility(move);
}
