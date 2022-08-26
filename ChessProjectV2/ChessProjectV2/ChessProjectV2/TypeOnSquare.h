#pragma once

#include "BitBoard.h"
#include "DataAndTypes.h"

class PieceTypeOnSquare
{
private:
	Square _pos;
	PieceType _chessType;
public:
	PieceTypeOnSquare(Square pos, PieceType type);
	
	Square getPos() const;
	PieceType getType() const;
};