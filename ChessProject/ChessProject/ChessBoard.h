#pragma once
#include "ChessPiece.h"
#include "Coordinate.h"
#include "Move.h"
class ChessBoard
{
protected:
	bool isWhiteTurn;
	ChessPiece board[BOARD_SIZE][BOARD_SIZE];
	void setPieceAt(ChessPiece* piece, Coordinate* coord);
	bool executeMove(Move* givenMove);
	//legal checks
	bool moveIsLegal(Move* givenMove); 
	bool typeMoveLegal(PieceType* piece, Move* givenMove);
public:
	ChessBoard();
	ChessPiece* getAtPosition(Coordinate* coord);
	ChessColor* getTurnColor();
private:
	void initBoard();
	//move checks
	bool straightLineCheck(Move* givenMove);
	bool diagonalLineCheck(Move* givenMove);
	//maths
	short ifNegativMakePositive(short a);
};