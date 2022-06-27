#include "Move.h"

Move::Move()
{
	start = Coordinate();
	destination = Coordinate();
}

Move::Move(
	Coordinate* givenStart,
	Coordinate* givenDestination)
{
	start = *givenStart;
	destination = *givenDestination;
}

Coordinate* Move::getStart()
{
	return &start;
}

Coordinate* Move::getDestination()
{
	return &destination;
}

bool Move::isValid()
{
	return
		start.isValid() &&
		destination.isValid() &&
		start != destination;
}