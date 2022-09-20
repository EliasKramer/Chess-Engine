#include "ChessBoardTest.h"

ChessBoardTest::ChessBoardTest(std::string given_fen_code)
	:ChessBoard(given_fen_code)
{}

BitBoard ChessBoardTest::getAllPieces()
{
	return _board._allPieces;
}

BitBoard ChessBoardTest::getAllPiecesOfColor(ChessColor color)
{
	return _board._piecesOfColor[color];
}

BitBoard ChessBoardTest::getAllPiecesOfType(PieceType type)
{
	return _board._piecesOfType[type];
}

bool ChessBoardTest::fieldIsUnderAttackWithMoveBB(Square pos, BitBoard moveBB)
{
	return ChessBoard::fieldIsUnderAttack(pos, moveBB);
}

bool ChessBoardTest::isLegal(const std::unique_ptr<Move>& move)
{
	return ChessBoard::moveIsLegal(move);
}

UniqueMoveList ChessBoardTest::getPseudoLegalMoves()
{
	return ChessBoard::getAllPseudoLegalMoves();
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