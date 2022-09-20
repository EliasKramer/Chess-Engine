#include "BoardRepresentation.h"

BoardRepresentation::BoardRepresentation()
	:
	_allPieces(BITBOARD_NONE),
	_piecesOfColor{
	BITBOARD_NONE,
	BITBOARD_NONE },

	_piecesOfType{
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE },
	
	_kingPos{E1, E8}
{}

BitBoard BoardRepresentation::getAllPieces() const
{
	return _allPieces;
}

BitBoard BoardRepresentation::getPiecesOfColor(ChessColor color) const
{
	return _piecesOfColor[color];
}

BitBoard BoardRepresentation::getPiecesOfType(PieceType type) const
{
	return _piecesOfType[type];
}

Square BoardRepresentation::getKingPos(ChessColor color) const
{
	return _kingPos[color];
}

void BoardRepresentation::setAllPieces(BitBoard allPieces)
{
	_allPieces = allPieces;
}

void BoardRepresentation::setPiecesOfColor(ChessColor color, BitBoard pieces)
{
	_piecesOfColor[color] = pieces;
}

void BoardRepresentation::setPiecesOfType(PieceType type, BitBoard pieces)
{
	_piecesOfType[type] = pieces;
}

void BoardRepresentation::setKingPos(ChessColor color, Square kingPos)
{
	_kingPos[color] = kingPos;
}

void BoardRepresentation::copySquareToPos(Square copyField, Square pasteField)
{
	BitBoard copyPos = BB_SQUARE[copyField];
	BitBoard pastePos = BB_SQUARE[pasteField];

	for (int i = 0; i < DIFFERENT_CHESS_COLORS; i++)
	{
		ChessColor currCol = (ChessColor)i;

		if ((_piecesOfColor[currCol] & copyPos) != 0)
		{
			_piecesOfColor[currCol] = _piecesOfColor[currCol] | pastePos;
		}
		else
		{
			_piecesOfColor[currCol] = _piecesOfColor[currCol] & (~pastePos);
		}
	}

	for (int i = 0; i < NUMBER_OF_DIFFERENT_PIECE_TYPES; i++)
	{
		PieceType currType = (PieceType)i;

		if ((_piecesOfType[currType] & copyPos) != 0)
		{
			_piecesOfType[currType] = _piecesOfType[currType] | pastePos;
		}
		else
		{
			_piecesOfType[currType] = _piecesOfType[currType] & (~pastePos);
		}
	}

	if ((_allPieces & copyPos) != 0)
	{
		_allPieces = _allPieces | pastePos;
	}
}

void BoardRepresentation::setAtPosition(ChessPiece piece, Square position)
{
	BitBoard piecePos = BB_SQUARE[position];

	_allPieces = _allPieces | piecePos;

	ChessColor col = piece.getColor();
	_piecesOfColor[col] = _piecesOfColor[col] | piecePos;

	PieceType type = piece.getType();
	_piecesOfType[type] = _piecesOfType[type] | piecePos;
}

void BoardRepresentation::delAtPos(Square position)
{
	BitBoard keepPiecesMask = ~(BB_SQUARE[position]);

	_allPieces = _allPieces & keepPiecesMask;

	for (int i = 0; i < DIFFERENT_CHESS_COLORS; i++)
	{
		ChessColor currCol = (ChessColor)i;
		_piecesOfColor[currCol] = _piecesOfColor[currCol] & keepPiecesMask;
	}

	for (int i = 0; i < NUMBER_OF_DIFFERENT_PIECE_TYPES; i++)
	{
		PieceType currType = (PieceType)i;
		_piecesOfType[currType] = _piecesOfType[currType] & keepPiecesMask;
	}
}

bool operator==(const BoardRepresentation& first, const BoardRepresentation& second)
{
	bool retVal = first._allPieces == second._allPieces
		&& (first._piecesOfColor[White] == second._piecesOfColor[White])
		&& (first._piecesOfColor[Black] == second._piecesOfColor[Black]);

	for (int i = 0; i < NUMBER_OF_DIFFERENT_PIECE_TYPES; i++)
	{
		retVal = retVal && (first._piecesOfType[i] == second._piecesOfType[i]);
	}

	retVal = retVal && (first._kingPos[White] == second._kingPos[White]);
	retVal = retVal && (first._kingPos[Black] == second._kingPos[Black]);

	return retVal;
}

bool operator!=(const BoardRepresentation& first, const BoardRepresentation& second)
{
    return !(first == second);
}