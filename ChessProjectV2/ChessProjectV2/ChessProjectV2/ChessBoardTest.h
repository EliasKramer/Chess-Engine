#pragma once
#include "ChessBoard.h"
class ChessBoardTest : public ChessBoard
{
	//getter for the base class
	BitBoard getAllPieces();
	BitBoard getAllPiecesOfColor();
};