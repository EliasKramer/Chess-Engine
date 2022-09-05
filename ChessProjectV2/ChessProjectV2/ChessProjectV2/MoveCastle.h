#pragma once
#include "Move.h"
#include "Constants.h"
class MoveCastle : public Move
{
private:
	Square _rookStart;
	Square _rookDest;
public:
	MoveCastle(Square givenStart, Square givenDest, Square rookStart, Square rookDest);
	MoveCastle(ChessColor color, CastlingType castlingType);

	Square getRookStart();
	Square getRookDest();

	void execute(
		std::function<void(Square, Square)> copySquare,
		std::function<void(ChessPiece, Square)> setAtPos,
		std::function<void(Square)> delAtPos) override;

	//castling does not produce a a bitboard, that you can use
	//it will just throw an error
	BitBoard getBBWithMoveDone() override;
};