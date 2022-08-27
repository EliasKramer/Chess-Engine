#pragma once
#include "BitBoard.h"
#include <memory>
#include <vector>

class Move
{
protected:
	Square _start;
	Square _destination;

	friend bool operator ==(const Move& first, const Move& second);
	friend bool operator !=(const Move& first, const Move& second);
public:
	Move(Square givenStart, Square givenDest);
	Square getStart();
	Square getDestination();
		
	//void execute();
};
bool operator ==(const Move& first, const Move& second);
bool operator !=(const Move& first, const Move& second);

typedef std::vector<std::unique_ptr<Move>> UniqueMoveList;