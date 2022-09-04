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

	//castling does not produce a a bitboard, that you can use
	//it will just throw an error
	BitBoard getBBWithMoveDone() override;
};