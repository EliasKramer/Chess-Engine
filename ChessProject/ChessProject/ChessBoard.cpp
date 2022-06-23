#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
	isWhiteTurn = true;
	initBoard();
}

ChessPiece* ChessBoard::getAtPosition(char file, unsigned short rank)
{
	return coordSetIsValid(file, rank) ?
		board[file2Coords(file),rank2Coords(rank)] :
		nullptr;
}

void ChessBoard::initBoard()
{
	ChessPiece wr = ChessPiece(PieceType::Rook, ChessColor::White);
	setPieceAt(&wr, 'a', 1);

	
}

void ChessBoard::setPieceAt(ChessPiece* piece, char file, unsigned short rank)
{
	int actualFile = file2Coords(file);
	int actualRank = rank2Coords(rank);
	if (actualFile != -1 && actualRank != -1)
	{
		ChessPiece toDel = board[actualFile][actualRank];
		board[actualFile][actualRank] = *piece;
		//delete& toDel;
	}
}

int ChessBoard::file2Coords(char file)
{
	int result = file - 'a';
	return coordIsValid(result) ? result : -1;
}

int ChessBoard::rank2Coords(unsigned short rank)
{
	int result = rank - 1;
	return coordIsValid(result) ? result : -1;
}

bool ChessBoard::coordIsValid(int coord)
{
	return coord < BOARD_SIZE && coord >= 0;
}

bool ChessBoard::coordSetIsValid(char file, unsigned short rank)
{
	return coordIsValid(file2Coords(file)) && coordIsValid(rank2Coords(rank));
}
