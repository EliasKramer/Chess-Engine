#pragma once
#include "BitBoard.h"
#include "DataAndTypes.h"
#include "TypeOnSquare.h"
#include <memory>
#include <vector>
class Move
{
private:
	//vectors are really big. might change that later to arrays or just vars
	std::vector<Square> _delSquares;
	std::vector<PieceTypeOnSquare> _piecesToSet;

	friend bool operator ==(const Move& first, const Move& second);
	friend bool operator !=(const Move& first, const Move& second);
public:
	Move(Square givenStart, Square givenDest, PieceType type);

	Square getStart();
	Square getDestination();
	PieceType getTypeAtDest();

	void addDeletionSquare(Square square);
	void addPieceToSetAt(Square position, PieceType type);

	//void execute();
	//if deletion field is an enemy -> it is en passant
	//if deletion friend -> it is normal move
};
bool operator ==(const Move& first, const Move& second);
bool operator !=(const Move& first, const Move& second);

typedef std::vector<Move> MoveList;