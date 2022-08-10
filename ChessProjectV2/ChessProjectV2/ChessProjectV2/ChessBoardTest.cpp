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

BitBoard ChessBoardTest::getAllAvailableCastleMoves()
{
    return _castlingAllowed;
}
