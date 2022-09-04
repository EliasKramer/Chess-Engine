#include "BitBoard.h"

bool destinationIsOnBoard(Square start, Direction direction)
{
	//if the invalid board for the direction and
	//the start square dont overlap then the new pos is valid
	return (INVALID_FIELDS_FOR_DIR.at(direction) & BB_SQUARE[start]) == 0;
}

bool squareOverlapsWithBB(Square pos, BitBoard bb)
{
	return (BB_SQUARE[pos] & bb) != 0;
}
