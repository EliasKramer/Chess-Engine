#pragma once

#include "Move.h"
class MoveEnPassant : public Move
{
private:
	Square _posToDel;
public:
	MoveEnPassant(Square givenStart, Square givenDest, Square posToDel);
};
