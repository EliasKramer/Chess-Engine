#pragma once
#include "Move.h"
class MoveCastle : public Move
{
private:
	Square _rookStart;
	Square _rookDest;
public:
	MoveCastle(Square givenStart, Square givenDest, Square rookStart, Square rookDest);
};