#pragma once
#include "ChessBoard.h"
class ChessBoardTest : public ChessBoard
{
public:
	void setPieceAt(
		ChessPiece piece,
		Coordinate coord);
	void clearPieceAt(Coordinate* coord);
	void clearBoard();
	void setLastMove(Move* move);
	Move getLastMove();
	std::vector<Move*> getAllMovesOfPiece(ChessPiece piece, Coordinate coord);
	//bool fieldGetsAttackedByEnemy(Coordinate* coord, ChessColor* color);
	RayCastResult executeSingleRayCast(
		RayCastOptions& options,
		short fileAddingVal,
		short rankAddingVal);
	ChessPiece getAtPostitionWithMoveDone(Coordinate* coord, Move* move);
	RayCastResult executeRayCast(
		PieceType type, 
		RayCastOptions& options,
		bool shouldCalculateIfItIsUnderAttack);
	bool fieldIsUnderAttack(Coordinate coord, ChessColor color);
	Coordinate searchForPiece(ChessPiece piece);
	bool isInCheck(ChessColor col);
	bool isInCheck(ChessColor col, Move move);
	void setCanCastle(ChessColor col, CastleType cType, bool value);
	bool getCanCastle(ChessColor col, CastleType cType);
	void setCanCastleAll(bool value);
	void updateCastlingAbility(Move move);
	ChessBoardTest getCopy();
};