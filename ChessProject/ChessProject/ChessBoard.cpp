#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
	isWhiteTurn = true;
	initBoard();
}

ChessPiece* ChessBoard::getAtPosition(char file, unsigned short rank)
{
	return nullptr;
}

void ChessBoard::initBoard()
{
	board[0][0] = ChessPiece(PieceType::Rook, ChessColor::White);
}

int ChessBoard::file2Coords(char file)
{
	return file - 'a';
}

int ChessBoard::rank2Coords(unsigned short rank)
{
	return rank-1;
}