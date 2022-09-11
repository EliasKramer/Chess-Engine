#pragma once
#include "BitBoard.h"
#include "DataAndTypes.h"
#include "ChessPiece.h"
#include <memory>
#include <vector>
#include <functional>
#include <string>
#include "Constants.h"
#include "BoardRepresentation.h"
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
	
	virtual void execute(BoardRepresentation& board);

	//xor this map to get a board for checking if king is in check
	virtual BitBoard getBBWithMoveDone();

	virtual std::string getString();
};
bool operator ==(const Move& first, const Move& second);
bool operator !=(const Move& first, const Move& second);

typedef std::vector<std::unique_ptr<Move>> UniqueMoveList;