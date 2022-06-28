#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
	isWhiteTurn = true;
	initBoard();
}

ChessPiece* ChessBoard::getAtPosition(Coordinate* coord)
{
	return coord->isValid() ?
		&board[coord->getFileAsPosition()][coord->getRankAsPosition()] :
		nullptr;
}

ChessColor* ChessBoard::getTurnColor()
{
	ChessColor white = ChessColor::White;
	ChessColor black = ChessColor::Black;
	return isWhiteTurn ? &white : &black;
}

bool ChessBoard::executeMove(Move* givenMove)
{
	if (givenMove->isValid())
	{
		setPieceAt(
			getAtPosition(
				givenMove->getStart()),
			givenMove->getDestination());
		return true;
	}
	return false;
}



void ChessBoard::setPieceAt(ChessPiece* piece, Coordinate* coord)
{
	if (coord->isValid())
	{
		int file = coord->getFileAsPosition();
		int rank = coord->getRankAsPosition();
		ChessPiece toDel = board[file][rank];
		board[file][rank] = *piece;
	}
}



void ChessBoard::initBoard()
{
	ChessPiece piece = ChessPiece(PieceType::Rook, ChessColor::White);
	Coordinate position = Coordinate('a', 1);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Knight, ChessColor::White);
	position = Coordinate('b', 1);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Bishop, ChessColor::White);
	position = Coordinate('c', 1);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Queen, ChessColor::White);
	position = Coordinate('d', 1);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::King, ChessColor::White);
	position = Coordinate('e', 1);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Bishop, ChessColor::White);
	position = Coordinate('f', 1);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Knight, ChessColor::White);
	position = Coordinate('g', 1);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Rook, ChessColor::White);
	position = Coordinate('h', 1);
	setPieceAt(&piece, &position);

	for (char file = 'a'; file <= 'h'; file++)
	{
		piece = ChessPiece(PieceType::Pawn, ChessColor::White);
		position = Coordinate(file, 2);
		setPieceAt(&piece, &position);

		piece = ChessPiece(PieceType::NoType, ChessColor::NoColor);
		for (int rank = 3; rank <= 6; rank++)
		{
			position = Coordinate(file, rank);
			setPieceAt(&piece, &position);
		}

		piece = ChessPiece(PieceType::Pawn, ChessColor::Black);
		position = Coordinate(file, 7);
		setPieceAt(&piece, &position);
	}

	piece = ChessPiece(PieceType::Rook, ChessColor::Black);
	position = Coordinate('a', 8);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Knight, ChessColor::Black);
	position = Coordinate('b', 8);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Bishop, ChessColor::Black);
	position = Coordinate('c', 8);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Queen, ChessColor::Black);
	position = Coordinate('d', 8);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::King, ChessColor::Black);
	position = Coordinate('e', 8);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Bishop, ChessColor::Black);
	position = Coordinate('f', 8);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Knight, ChessColor::Black);
	position = Coordinate('g', 8);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Rook, ChessColor::Black);
	position = Coordinate('h', 8);
	setPieceAt(&piece, &position);
}
short ChessBoard::ifNegativMakePositive(short a)
{
	return a < 0 ? -a : a;
}
bool ChessBoard::moveIsLegal(Move* givenMove)
{
	if (!givenMove->isValid())
	{
		return false;
	}

	ChessPiece* piece = getAtPosition(givenMove->getStart());
	if (!piece->isValid())
	{
		return false;
	}

	bool pieceToMoveIsWhite =
		*piece->getColor() == ChessColor::White;
	if (isWhiteTurn != pieceToMoveIsWhite)
	{
		return false;
	}

	if (!pieceIsAlledToMoveInThisWay(piece, givenMove))
	{
		return false;
	}

	return true;
}

bool ChessBoard::pieceIsAlledToMoveInThisWay(ChessPiece* piece, Move* givenMove)
{
	switch (*piece->getType())
	{
	case PieceType::Rook:
		return 
			straightLineCheck(givenMove);
	case PieceType::Bishop:
		return 
			diagonalLineCheck(givenMove);
	case PieceType::Queen:
		return 
			straightLineCheck(givenMove) ||
			diagonalLineCheck(givenMove);
	case PieceType::Knight:
		return 
			knightMoveCheck(givenMove);
	case PieceType::King:
		return 
			kingMoveCheck(givenMove);
	case PieceType::Pawn:
		return true;
	default:
		return false;
		break;
	}
}

bool ChessBoard::straightLineCheck(Move* givenMove)
{
	Coordinate* start = givenMove->getStart();
	Coordinate* dest = givenMove->getDestination();

	return (start->getFileAsPosition() == dest->getFileAsPosition()) ||
		(start->getRankAsPosition() == dest->getRankAsPosition());
}

bool ChessBoard::diagonalLineCheck(Move* givenMove)
{
	Coordinate* start = givenMove->getStart();
	Coordinate* dest = givenMove->getDestination();
	return ifNegativMakePositive((short)start->getFileAsPosition() - (short)dest->getFileAsPosition()) ==
		ifNegativMakePositive((short)start->getRankAsPosition() - (short)dest->getRankAsPosition());
}

bool ChessBoard::knightMoveCheck(Move* givenMove)
{
	Coordinate* start = givenMove->getStart();
	Coordinate* dest = givenMove->getDestination();
	short fileDiff = ifNegativMakePositive((short)start->getFileAsPosition() - (short)dest->getFileAsPosition());
	short rankDiff = ifNegativMakePositive((short)start->getRankAsPosition() - (short)dest->getRankAsPosition());
	return (fileDiff == 1 && rankDiff == 2) ||
		(fileDiff == 2 && rankDiff == 1);
}

bool ChessBoard::kingMoveCheck(Move* givenMove)
{
	Coordinate* start = givenMove->getStart();
	Coordinate* dest = givenMove->getDestination();
	short fileDiff = ifNegativMakePositive((short)start->getFileAsPosition() - (short)dest->getFileAsPosition());
	short rankDiff = ifNegativMakePositive((short)start->getRankAsPosition() - (short)dest->getRankAsPosition());
	return (fileDiff <= 1 && rankDiff <= 1);
}

bool ChessBoard::pawnMoveCheck(Move* givenMove)
{
	Coordinate* start = givenMove->getStart();
	Coordinate* dest = givenMove->getDestination();
	short fileDiff = ifNegativMakePositive((short)start->getFileAsPosition() - (short)dest->getFileAsPosition());
	short rankDiff = ifNegativMakePositive((short)start->getRankAsPosition() - (short)dest->getRankAsPosition());
	return (fileDiff == 0 && rankDiff == 1);
}
