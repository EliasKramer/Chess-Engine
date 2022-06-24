#pragma once
#include "ChessPiece.h"
#include "Coordinate.h"

class ChessBoard
{
private:
	ChessPiece board[BOARD_SIZE][BOARD_SIZE];
	bool isWhiteTurn;
public:
	ChessBoard();
	ChessPiece* getAtPosition(Coordinate* coord);
private:
	void initBoard();
protected:
	void setPieceAt(ChessPiece* piece, Coordinate* coord);
};