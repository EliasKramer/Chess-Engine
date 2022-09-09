#pragma once
#include "BitBoard.h"
#include "DataAndTypes.h"
#include "ChessPiece.h"
#include <memory>
#include <vector>
#include <functional>

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
	
	virtual void execute(
		std::function<void(Square, Square)> copySquare,
		std::function<void(ChessPiece, Square)> setAtPos,
		std::function<void(Square)> delAtPos);

	//xor this map to get a board for checking if king is in check
	virtual BitBoard getBBWithMoveDone();
};
bool operator ==(const Move& first, const Move& second);
bool operator !=(const Move& first, const Move& second);

typedef std::vector<std::unique_ptr<Move>> UniqueMoveList;