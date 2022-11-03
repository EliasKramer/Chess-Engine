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
private:
	Square _start;
	Square _destination;
	MoveFlag _flag;

	friend bool operator ==(const Move& first, const Move& second);
	friend bool operator !=(const Move& first, const Move& second);
public:
	Move(Square givenStart, Square givenDest, MoveFlag flag = MoveFlag::Normal);
	
	Square getStart() const;
	Square getDestination() const;
	
	void execute(BoardRepresentation& board);

	virtual std::string getString() const;
};
bool operator ==(const Move& first, const Move& second);
bool operator !=(const Move& first, const Move& second);

typedef std::vector<Move> MoveList;