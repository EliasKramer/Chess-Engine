#pragma once
#include "BitBoard.h"

class ChessBoard
{
protected:
	BitBoard _allPieces;
	BitBoard _blackPieces;
	BitBoard _whitePieces;
	BitBoard _pawns;
	BitBoard _rooks;
	BitBoard _bishops;
	BitBoard _knights;
	BitBoard _queens;
	BitBoard _kings;
	
	//keeps track of fields, where rooks and kings are standing
	//if a move starts or end on one of these fields, the castling gets disabled on that side
	BitBoard _castlingAllowed;
public:
	ChessBoard();
	void setupBoard();
};