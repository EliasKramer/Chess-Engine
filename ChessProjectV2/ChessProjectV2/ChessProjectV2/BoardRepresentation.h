#pragma once
#include "BitBoard.h"
#include "DataAndTypes.h"
#include "Constants.h"
#include "ChessPiece.h"

class BoardRepresentation
{
public:
	BitBoard _allPieces;
	BitBoard _piecesOfColor[DIFFERENT_CHESS_COLORS];
	BitBoard _piecesOfType[NUMBER_OF_DIFFERENT_PIECE_TYPES];

	Square _kingPos[DIFFERENT_CHESS_COLORS];

	//TODO implement this
	uint8_t _pieceCount[DIFFERENT_CHESS_COLORS][NUMBER_OF_DIFFERENT_PIECE_TYPES];
	
	BoardRepresentation();

	void copySquareToPos(Square copyField, Square pasteField);
	void setAtPosition(ChessPiece piece, Square position);
	void delAtPos(Square position);
};
bool operator==(const BoardRepresentation& first, const BoardRepresentation& second);
bool operator!=(const BoardRepresentation& first, const BoardRepresentation& second);