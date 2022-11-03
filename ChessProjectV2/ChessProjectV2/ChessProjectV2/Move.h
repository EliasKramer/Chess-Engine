#pragma once
#include <functional>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

#include "BitBoard.h"
#include "DataAndTypes.h"
#include "ChessPiece.h"
#include "Constants.h"
#include "BoardRepresentation.h"

class Move
{
private:
	Square _start;
	Square _destination;
	MoveFlag _flag;
	ChessColor _colorOfPiece;

	friend bool operator ==(const Move& first, const Move& second);
	friend bool operator !=(const Move& first, const Move& second);
public:
	//for normal and en passant moves
	Move(Square givenStart, Square givenDest, MoveFlag flag = MoveFlag::Normal);
	//for promoting moves
	Move(Square givenStart, Square givenDest, ChessColor color ,MoveFlag flag = MoveFlag::Normal);
	//for castling moves
	Move(ChessColor col, CastlingType castleType);

	Square getStart() const;
	Square getDestination() const;
	
	void execute(BoardRepresentation& board);

	virtual std::string getString() const;
};
bool operator ==(const Move& first, const Move& second);
bool operator !=(const Move& first, const Move& second);

typedef std::vector<Move> MoveList;