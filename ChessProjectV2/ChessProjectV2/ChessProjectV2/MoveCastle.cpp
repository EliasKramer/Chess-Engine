#include "MoveCastle.h"

MoveCastle::MoveCastle(Square givenStart, Square givenDest, Square rookStart, Square rookDest)
	:Move(givenStart, givenDest),
	_rookStart(rookStart),
	_rookDest(rookDest)
{}