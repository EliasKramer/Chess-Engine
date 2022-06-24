#pragma once
#include "ChessBoard.h"
class ChessBoardTest : public ChessBoard
{
public:
	void setPieceAt(ChessPiece* piece, Coordinate* coord);
};