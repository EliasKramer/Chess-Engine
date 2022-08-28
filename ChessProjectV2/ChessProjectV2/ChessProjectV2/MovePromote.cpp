#include "MovePromote.h"

MovePromote::MovePromote(Square givenStart, Square givenDest, PieceType promotingType)
	:Move(givenStart, givenDest),
	_promotingType(promotingType)
{}