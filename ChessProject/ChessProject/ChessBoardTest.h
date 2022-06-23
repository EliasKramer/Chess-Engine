#pragma once
#include "ChessBoard.h"
class ChessBoardTest : public ChessBoard
{
public:
	int file2Coords(char file);
	int rank2Coords(unsigned short rank);
	bool coordIsValid(int coord);
	bool coordSetIsValid(char file, unsigned short rank);
	void setPieceAt(ChessPiece* piece, char file, unsigned short rank);
};