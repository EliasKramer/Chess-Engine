#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
	isWhiteTurn = true;
	initBoard();
}

ChessPiece* ChessBoard::getAtPosition(Coordinate* coord)
{
	return coord->isValid() ?
		board[coord->getFileAsPosition(), coord->getRankAsPosition()] :
		nullptr;
}



void ChessBoard::setPieceAt(ChessPiece* piece, Coordinate* coord)
{
	if (coord->isValid())
	{
		int file = coord->getFileAsPosition();
		int rank = coord->getRankAsPosition();
		ChessPiece toDel = 
			board[file][rank];
		board[file][rank] = *piece;
		//delete& toDel;
	}
}

void ChessBoard::initBoard()
{
	ChessPiece wr = ChessPiece(PieceType::Rook, ChessColor::White);
	//setPieceAt(&wr, 'a', 1);
}