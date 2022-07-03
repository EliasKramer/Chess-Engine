#pragma once
#include "ChessPiece.h"
#include "Coordinate.h"
#include "Move.h"
#include <list>
class ChessBoard
{
protected:
	bool isWhiteTurn;
	ChessPiece board[BOARD_SIZE][BOARD_SIZE];
	void setPieceAt(ChessPiece* piece, Coordinate* coord);
	bool executeMove(Move* givenMove);
	std::list<Move> getAllMovesInDirection(
		Coordinate* start,
		ChessColor* color,
		short fileAddingValue,
		short rankAddingValue);
	std::list<Move> getAllMovesOfPiece(ChessPiece* piece, Coordinate* coord);
public:
	ChessBoard();
	ChessPiece* getAtPosition(Coordinate* coord);
	ChessColor* getTurnColor();
	std::list<Move> getAllMoves();
private:
	void initBoard();
	std::list<Move> getAllStraightMoves(ChessColor* color, Coordinate* coord);
	std::list<Move> getAllDiagonalMoves(ChessColor* color, Coordinate* coord);
	std::list<Move> getAllQueenMoves(ChessColor* color, Coordinate* coord);
	std::list<Move> getAllKnightMoves(ChessColor* color, Coordinate* coord);
	std::list<Move> getAllPawnMoves(ChessColor* color, Coordinate* coord);
	std::list<Move> getAllKingMoves(ChessColor* color, Coordinate* coord);
	bool ifCanGoThereAdd(ChessColor* currColor, Move* move, std::list<Move>& possibleMoves);
};