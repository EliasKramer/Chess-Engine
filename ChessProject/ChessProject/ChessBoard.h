#pragma once
#include "ChessPiece.h"
#include "Coordinate.h"
#include "Move.h"
#include "RayCastOptions.h"
#include "RayCastResult.h"
#include <list>
class ChessBoard
{
protected:
	bool isWhiteTurn;
	ChessPiece board[BOARD_SIZE][BOARD_SIZE];
	Move lastMove;

	void setPieceAt(ChessPiece* piece, Coordinate* coord);
	bool executeMove(Move* givenMove);
	std::list<Move> getAllMovesInDirection(
		Coordinate* start,
		ChessColor* color,
		short fileAddingValue,
		short rankAddingValue);
	std::list<Move> getAllMovesOfPiece(ChessPiece* piece, Coordinate* coord);
	void setLastMove(Move* move);
	//no pointer to avoid setting it without permission
	Move getLastMove();
	//bool fieldIsUnderAttack(Coordinate* coord, ChessColor* color);
	RayCastResult* executeRayCast(RayCastOptions* options);
	
public:
	//constructor
	ChessBoard();
	//aquire piece at the given coordinate
	ChessPiece* getAtPosition(Coordinate* coord);
	//get the color of the current turn
	ChessColor* getTurnColor();
	//get all possible moves that can be made
	std::list<Move> getAllMoves();
private:
	//set the board up
	void initBoard();
	
	//todo
	//with fn pointers for different purposes
	//void addIfNoPiece

	//all the moves that can be made by a piece
	std::list<Move> getAllStraightMoves(ChessColor* color, Coordinate* coord);
	std::list<Move> getAllDiagonalMoves(ChessColor* color, Coordinate* coord);
	std::list<Move> getAllQueenMoves(ChessColor* color, Coordinate* coord);
	std::list<Move> getAllKnightMoves(ChessColor* color, Coordinate* coord);
	std::list<Move> getAllPawnMoves(ChessColor* color, Coordinate* coord);
	std::list<Move> getAllKingMoves(ChessColor* color, Coordinate* coord);
	//help function for above functions
	bool ifCanGoThereAdd(ChessColor* currColor, Move* move, std::list<Move>& possibleMoves);
};