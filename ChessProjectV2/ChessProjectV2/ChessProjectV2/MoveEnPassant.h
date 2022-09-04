#pragma once

#include "Move.h"
class MoveEnPassant : public Move
{
private:
	Square _posToDel;
public:
	MoveEnPassant(Square givenStart, Square givenDest, Square posToDel);

	//xor this map to get a board for checking if king is in check
	BitBoard getBBWithMoveDone() override;
};
