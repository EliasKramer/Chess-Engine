#pragma once
#include "Move.h"
class MoveDoublePawn : public Move
{
private:
	Square _setEnPassantField;
public:
	MoveDoublePawn(Square givenStart, Square givenDest, Square setEnPassantField);
};