#include "ChessBoardTest.h"

int ChessBoardTest::file2Coords(char file)
{
    return ChessBoard::file2Coords(file);
}
int ChessBoardTest::rank2Coords(unsigned short rank)
{
    return ChessBoard::rank2Coords(rank);
}
bool ChessBoardTest::coordIsValid(int coord)
{
    return ChessBoard::coordIsValid(coord);
}

bool ChessBoardTest::coordSetIsValid(char file, unsigned short rank)
{
    return ChessBoard::coordSetIsValid(file,rank);
}

void ChessBoardTest::setPieceAt(ChessPiece* piece, char file, unsigned short rank)
{
    ChessBoard::setPieceAt(piece, file, rank);
}
