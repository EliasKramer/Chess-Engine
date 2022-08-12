#include "ChessBoardTest.h"

ChessBoardTest::ChessBoardTest()
    :ChessBoard()
{}

ChessBoardTest::ChessBoardTest(std::string given_fen_code)
    :ChessBoard(given_fen_code)
{}

BitBoard ChessBoardTest::getAllPieces()
{
    return _allPieces;
}

BitBoard ChessBoardTest::getAllPiecesOfColor(ChessColor color)
{
    return _piecesOfColor[color];
}

BitBoard ChessBoardTest::getAllPiecesOfType(PieceType type)
{
    return _piecesOfType[type];
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
    return _lastEnPassantMove;
}

uint16_t ChessBoardTest::getHalfMovesSinceLastCaptureOrPawnMove()
{
    return _halfMovesSincePawnOrCaptureMove;
}

uint16_t ChessBoardTest::getMoveNumber()
{
    return _moveNumber;
}