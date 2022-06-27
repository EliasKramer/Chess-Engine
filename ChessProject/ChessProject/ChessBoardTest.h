#pragma once
#include "ChessBoard.h"
class ChessBoardTest : public ChessBoard
{
public:
	void setPieceAt(
		ChessPiece* piece,
		Coordinate* coord);
	void clearBoard();
	void setTurnColor(ChessColor* color);
	bool executeMove(Move* givenMove);
	bool moveIsLegal(Move* givenMove);
	bool typeMoveLegal(PieceType* type, Move* givenMove);
};