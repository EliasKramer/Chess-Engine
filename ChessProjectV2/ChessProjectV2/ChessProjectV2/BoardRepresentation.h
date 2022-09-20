#pragma once
#include "BitBoard.h"
#include "DataAndTypes.h"
#include "Constants.h"
#include "ChessPiece.h"

class BoardRepresentation
{
private:
	BitBoard _allPieces;
	BitBoard _piecesOfColor[DIFFERENT_CHESS_COLORS];
	BitBoard _piecesOfType[NUMBER_OF_DIFFERENT_PIECE_TYPES];

	Square _kingPos[DIFFERENT_CHESS_COLORS];

	friend bool operator==(const BoardRepresentation& first, const BoardRepresentation& second);
	friend bool operator!=(const BoardRepresentation& first, const BoardRepresentation& second);
public:
	BoardRepresentation();

	//getters
	BitBoard getAllPieces() const;
	BitBoard getPiecesOfColor(ChessColor color) const;
	BitBoard getPiecesOfType(PieceType type) const;
	Square getKingPos(ChessColor color) const;

	//setters
	void setAllPieces(BitBoard allPieces);
	void setPiecesOfColor(ChessColor color, BitBoard pieces);
	void setPiecesOfType(PieceType type, BitBoard pieces);
	void setKingPos(ChessColor color, Square kingPos);

	void copySquareToPos(Square copyField, Square pasteField);
	void setAtPosition(ChessPiece piece, Square position);
	void delAtPos(Square position);
};
bool operator==(const BoardRepresentation& first, const BoardRepresentation& second);
bool operator!=(const BoardRepresentation& first, const BoardRepresentation& second);