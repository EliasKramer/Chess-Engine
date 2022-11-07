#pragma once
#include "BitBoard.h"
#include "DataAndTypes.h"
#include "Constants.h"
#include "ChessPiece.h"
#include <vector>

class BoardRepresentation
{
public:
	BitBoard AllPieces;
	BitBoard PiecesOfColor[DIFFERENT_CHESS_COLORS];
	BitBoard PiecesOfType[NUMBER_OF_DIFFERENT_PIECE_TYPES];

	Square KingPos[DIFFERENT_CHESS_COLORS];

	//a list of all piece positions. first index is color, second is piece type
	std::vector<Square> PiecePositions[DIFFERENT_CHESS_COLORS][NUMBER_OF_DIFFERENT_PIECE_TYPES];

	BoardRepresentation();

	ChessPiece getPieceAt(Square square) const;

	void copySquareToPos(Square copyField, Square pasteField);
	//be aware, that this does not overwrite the square, it only adds it
	void setAtPosition(ChessPiece piece, Square position);

	void delAtPos(Square position);

	void moveFromPosToPos(Square start, Square destination);

private:
	//be aware, that this does not overwrite the Bitboard, it only adds it
	void setPieceBitBoard(ChessPiece piece, BitBoard bitboard);

	void removeFromPieceList(ChessPiece piece, Square position);
	void removeAllFromPieceListAt(Square position);
};
bool operator==(const BoardRepresentation& first, const BoardRepresentation& second);
bool operator!=(const BoardRepresentation& first, const BoardRepresentation& second);