#pragma once
#include "ChessPiece.h"
#include "Coordinate.h"
#include "Move.h"
#include "MovePawnPromotion.h"
#include "MoveCastle.h"
#include "MoveEnPassant.h"
#include "RayCastOptions.h"
#include "RayCastResult.h"
#include "MetaData.h"
#include <vector>
#include <memory>
class ChessBoard
{
public:
	//constructor
	ChessBoard();
	//aquire piece at the given coordinate
	ChessPiece getAtPosition(Coordinate coord);
	//get all possible moves that can be made
	std::vector<std::unique_ptr<Move>> getAllMoves(ChessColor color);

	std::string toString(ChessColor color);

	void executeMove(Move* givenMove);

protected:
	ChessPiece board[BOARD_SIZE][BOARD_SIZE];
	Move lastMove;
	bool canCastle[2][2];

	void updateCastlingAbility(Move move);
	
	void setCanCastle(ChessColor col, CastleType cType, bool value);

	bool getCanCastle(ChessColor col, CastleType cType);

	void setPieceAt(ChessPiece piece, Coordinate coord);

	Coordinate searchForPiece(ChessPiece piece);
	
	std::vector<std::unique_ptr<Move>> getAllMovesOfPiece(ChessPiece piece, Coordinate coord);
	
	void setLastMove(Move* move);
	
	Move getLastMove();	

	ChessPiece getAtPostitionWithMoveDone(Coordinate coord, Move* move);

	bool fieldIsUnderAttack(Coordinate coord, ChessColor color);
	
	bool fieldIsUnderAttack(Coordinate coord, ChessColor color, Move madeMove);
	
	bool isInCheck(ChessColor col);

	bool isInCheck(ChessColor col, Move madeMove);
private:
	//set the board up
	void initBoard();

protected:
	/*--- Raycasts ---*/
	
	//execute a single raycast
	RayCastResult executeSingleRayCast(
		RayCastOptions& options,
		short fileAddingVal,
		short rankAddingVal);
	//execute a raycast for a given piece type. except pawns
	RayCastResult executeRayCast(
		PieceType type,
		RayCastOptions& options,
		bool shouldCalculateIfItIsUnderAttack);
private:
	RayCastResult executeStraightLineRayCast(
		RayCastOptions& options,
		bool shouldCalculateIfItIsUnderAttack);
	RayCastResult executeDiagonalRayCast(
		RayCastOptions& options,
		bool shouldCalculateIfItIsUnderAttack);
	RayCastResult executeQueenRayCast(
		RayCastOptions& options,
		bool shouldCalculateIfItIsUnderAttack);
	RayCastResult executeKnightRayCast(
		RayCastOptions& options,
		bool shouldCalculateIfItIsUnderAttack);
	RayCastResult executeKingRayCast(
		RayCastOptions& options,
		bool shouldCalculateIfItIsUnderAttack);

	void calculateIfRayCastResultIsUnderAttackByType(
		PieceType type,
		RayCastResult& rcResult,
		Move imaginaryMove);

	/*--- Raycasts ---*/

	/*--- Castling ---*/

	void addCastleMovesIfPossibleForColor(ChessColor col, std::vector<std::unique_ptr<Move>>& moves);

	bool fieldIsEmptyAndNotUnderAttack(ChessColor col, Coordinate coord);

	/*--- Castling ---*/

	/*--- Pawn Move Set ---*/

	//all the moves that can be made by a pawn
	std::vector<std::unique_ptr<Move>> getAllPawnMoves(ChessColor color, Coordinate coord);

	//add all types of promotion moves
	void addPromotionMoves(
		Coordinate start,
		Coordinate dest,
		std::vector<std::unique_ptr<Move>>& moves);

	//all the fields that a pawn can attack.
	//not including en passant moves, since this is only used for checking if
	//a king is under check or can castle
	bool fieldGetsAttackedByPawn(Coordinate coord, ChessColor color, Move madeMove);
	
	/*--- Pawn Move Set ---*/
};