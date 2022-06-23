#pragma once
#include "ChessPiece.h"

class ChessBoard
{
private:
	ChessPiece board[BOARD_SIZE][BOARD_SIZE];
	bool isWhiteTurn;
public:
	ChessBoard();
	ChessPiece* getAtPosition(char file, unsigned short rank);
private:
	void initBoard();
	int file2Coords(char file);
	int rank2Coords(unsigned short rank);
};