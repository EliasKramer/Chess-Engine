#include "BoardRepresentation.h"

BoardRepresentation::BoardRepresentation()
	:
	AllPieces(BITBOARD_NONE),
	PiecesOfColor{
	BITBOARD_NONE,
	BITBOARD_NONE },

	PiecesOfType{
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE },
	
	KingPos{E1, E8}
{}

ChessPiece BoardRepresentation::getPieceAt(Square square) const
{
	BitBoard squareBB = BB_SQUARE[square];
	//can be improved by adding null types
	ChessColor colFound = NoColor;
	PieceType typeFound = NoType;

	for (int i = 0; i < DIFFERENT_CHESS_COLORS; i++)
	{
		ChessColor currCol = (ChessColor)i;

		if (bitboardsOverlap(PiecesOfColor[currCol], squareBB))
		{
			colFound = currCol;
			break;
		}
	}
	for (int i = 0; i < NUMBER_OF_DIFFERENT_PIECE_TYPES; i++)
	{
		PieceType currType = (PieceType)i;

		if (bitboardsOverlap(PiecesOfType[currType], squareBB))
		{
			typeFound = currType;
			break;
		}
	}

	return ChessPiece(colFound, typeFound);
}

void BoardRepresentation::setAtPosition(ChessPiece piece, Square position)
{
	if(piece.getType() == King)
	{
		KingPos[piece.getColor()] = position;
	}

	PiecePositions[piece.getColor()][piece.getType()].push_back(position);

	setPieceBitBoard(piece, BB_SQUARE[position]);
}

void BoardRepresentation::delAtPos(Square position)
{
	BitBoard keepPiecesMask = ~(BB_SQUARE[position]);

	AllPieces = AllPieces & keepPiecesMask;

	for (int i = 0; i < DIFFERENT_CHESS_COLORS; i++)
	{
		ChessColor currCol = (ChessColor)i;
		PiecesOfColor[currCol] = PiecesOfColor[currCol] & keepPiecesMask;
	}

	for (int i = 0; i < NUMBER_OF_DIFFERENT_PIECE_TYPES; i++)
	{
		PieceType currType = (PieceType)i;
		PiecesOfType[currType] = PiecesOfType[currType] & keepPiecesMask;
	}

	removeAllFromPieceListAt(position);
}

void BoardRepresentation::moveFromPosToPos(Square start, Square destination)
{
	BitBoard startPosBB = BB_SQUARE[start];
	BitBoard destPosBB = BB_SQUARE[destination];

	ChessPiece startPiece = getPieceAt(start);
	ChessPiece destPiece = getPieceAt(destination);

	//if there is not piece to move return
	if (!startPiece.isValid())
	{
		return;
	}
	if (destPiece.isValid())
	{
		delAtPos(destination);
	}

	//add piece to the color bitboard
	PiecesOfColor[startPiece.getColor()] = PiecesOfColor[startPiece.getColor()] | destPosBB;
	//add piece to the type bitboard
	PiecesOfType[startPiece.getType()] = PiecesOfType[startPiece.getType()] | destPosBB;
	//add piece to the all bitbaord
	AllPieces = AllPieces | destPosBB;

	delAtPos(start);
}

void BoardRepresentation::setPieceBitBoard(ChessPiece piece, BitBoard bitboard)
{
	AllPieces = AllPieces | bitboard;

	ChessColor col = piece.getColor();
	PiecesOfColor[col] = PiecesOfColor[col] | bitboard;

	PieceType type = piece.getType();
	PiecesOfType[type] = PiecesOfType[type] | bitboard;
}

void BoardRepresentation::removeFromPieceList(ChessPiece piece, Square position)
{
	std::vector<Square>& pieceList = PiecePositions[piece.getColor()][piece.getType()];

	for (int i = 0; i < pieceList.size(); i++)
	{
		if (pieceList[i] == position)
		{
			pieceList.erase(pieceList.begin() + i);
			break;
		}
	}
}

void BoardRepresentation::removeAllFromPieceListAt(Square position)
{
	for (int i = 0; i < DIFFERENT_CHESS_COLORS; i++)
	{
		ChessColor currCol = (ChessColor)i;

		for (int j = 0; j < NUMBER_OF_DIFFERENT_PIECE_TYPES; j++)
		{
			PieceType currType = (PieceType)j;

			removeFromPieceList(ChessPiece(currCol, currType), position);
		}
	}
}

//Equals Operator

bool operator==(const BoardRepresentation& first, const BoardRepresentation& second)
{
	bool retVal = first.AllPieces == second.AllPieces
		&& (first.PiecesOfColor[White] == second.PiecesOfColor[White])
		&& (first.PiecesOfColor[Black] == second.PiecesOfColor[Black]);

	for (int i = 0; i < NUMBER_OF_DIFFERENT_PIECE_TYPES; i++)
	{
		retVal = retVal && (first.PiecesOfType[i] == second.PiecesOfType[i]);
	}

	retVal = retVal && (first.KingPos[White] == second.KingPos[White]);
	retVal = retVal && (first.KingPos[Black] == second.KingPos[Black]);

	return retVal;
}

bool operator!=(const BoardRepresentation& first, const BoardRepresentation& second)
{
    return !(first == second);
}