#pragma once
#include "BitBoard.h"
#include "DataAndTypes.h"
#include <string>
class ChessBoard
{
protected:
	BitBoard _allPieces;
	BitBoard _piecesOfColor[DIFFERENT_CHESS_COLORS];
	BitBoard _piecesOfType[NUMBER_OF_DIFFERENT_PIECE_TYPES];
	
	//keeps track of fields, where rooks and kings are standing
	//if a move starts or end on one of these fields, the castling gets disabled on that side
	BitBoard _castlingAllowed;
public:
	ChessBoard();
	ChessBoard(std::string given_fen_code);
	void setupBoard();
};