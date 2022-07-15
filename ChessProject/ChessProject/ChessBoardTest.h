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
	void setLastMove(Move* move);
	Move getLastMove();
	std::vector<Move> getAllMovesInDirection(
		Coordinate* start,
		ChessColor* color,
		short fileAddingValue,
		short rankAddingValue);
	std::vector<Move> getAllMovesOfPiece(ChessPiece* piece, Coordinate* coord);
	//bool fieldGetsAttackedByEnemy(Coordinate* coord, ChessColor* color);
	RayCastResult executeRayCast(RayCastOptions* options);
	ChessPiece getAtPostitionWithMoveDone(Coordinate* coord, Move* move);
};