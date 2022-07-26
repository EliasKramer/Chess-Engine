#pragma once
#include "ChessPiece.h"
#include "Coordinate.h"
#include <functional>
class Move
{
protected:
	Coordinate start;
	Coordinate destination;
public:
	Move();
	Move(Coordinate* givenStart,
		Coordinate* givenDestination);
	virtual ~Move();
	
	Coordinate getStart();
	Coordinate getDestination();
	bool isValid();

	virtual void execute(
		std::function<ChessPiece(Coordinate*)> getAtPosition,
		std::function<void(ChessPiece*, Coordinate*)> setPieceAt);

	bool operator ==(const Move& other) const;
	bool operator !=(const Move& other) const;
};