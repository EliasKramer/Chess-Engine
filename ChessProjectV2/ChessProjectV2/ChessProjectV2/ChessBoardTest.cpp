#include "ChessBoardTest.h"

ChessBoardTest::ChessBoardTest(std::string given_fen_code)
	:ChessBoard(given_fen_code)
{}

BitBoard ChessBoardTest::getAllPieces()
{
	return _board.AllPieces;
}

BitBoard ChessBoardTest::getAllPiecesOfColor(ChessColor color)
{
	return _board.PiecesOfColor[color];
}

BitBoard ChessBoardTest::getAllPiecesOfType(PieceType type)
{
	return _board.PiecesOfType[type];
}

bool ChessBoardTest::isLegal(const Move move)
{
	return ChessBoard::moveIsLegal(move);
}

bool ChessBoardTest::casltingAllowed(ChessColor color, CastlingType option)
{
	return _canCastle[color][option];
}

ChessColor ChessBoardTest::getTurnColor()
{
	return _currentTurnColor;
}

Square ChessBoardTest::getEnPassantSquare()
{
	return _enPassantSquare;
}

uint16_t ChessBoardTest::getHalfMoveClock()
{
	return _halfMoveClock;
}

bool ChessBoardTest::fieldIsUnderAttack(Square pos)
{
	return ChessBoard::fieldIsUnderAttack(pos);
}

uint16_t ChessBoardTest::getMoveNumber()
{
	return _moveNumber;
}