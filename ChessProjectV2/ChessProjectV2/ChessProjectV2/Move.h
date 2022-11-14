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
	ChessColor _color_of_piece;

	friend bool operator ==(const Move& first, const Move& second);
	friend bool operator !=(const Move& first, const Move& second);
public:
	//for normal and en passant moves
	Move(Square given_start, Square given_destination, MoveFlag flag = MoveFlag::normal);
	//for promoting moves
	Move(Square given_start, Square given_destination, ChessColor color ,MoveFlag flag = MoveFlag::normal);
	//for castling moves
	Move(ChessColor col, CastlingType castle_type);

	Square get_start() const;
	Square get_destination() const;
	MoveFlag get_flag() const;
	
	void execute(BoardRepresentation& board) const;

	virtual std::string get_string() const;
};
bool operator ==(const Move& first, const Move& second);
bool operator !=(const Move& first, const Move& second);

typedef std::vector<Move> MoveList;