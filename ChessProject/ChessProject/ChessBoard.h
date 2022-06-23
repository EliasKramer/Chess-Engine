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
protected:
	int file2Coords(char file);
	int rank2Coords(unsigned short rank);
	bool coordIsValid(int coord);
	bool coordSetIsValid(char file, unsigned short rank);
	void setPieceAt(ChessPiece* piece, char file, unsigned short rank);
};