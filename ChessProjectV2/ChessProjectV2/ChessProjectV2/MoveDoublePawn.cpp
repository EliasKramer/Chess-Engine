#include "MoveDoublePawn.h"

MoveDoublePawn::MoveDoublePawn(Square givenStart, Square givenDest, Square setEnPassantField)
	:Move(givenStart, givenDest),
	_setEnPassantField(setEnPassantField)
{}
