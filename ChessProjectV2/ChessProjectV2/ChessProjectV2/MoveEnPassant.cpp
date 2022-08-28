#include "MoveEnPassant.h"

MoveEnPassant::MoveEnPassant(Square givenStart, Square givenDest, Square posToDel)
	: Move(givenStart, givenDest),
	_posToDel(posToDel)
{}