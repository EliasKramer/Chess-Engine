#include "MoveCastle.h"

MoveCastle::MoveCastle(Square givenStart, Square givenDest, Square rookStart, Square rookDest)
	:Move(givenStart, givenDest),
	_rookStart(rookStart),
	_rookDest(rookDest)
{}

MoveCastle::MoveCastle(ChessColor color, CastlingType castlingType)
	:Move(SQUARES_FOR_KING_CASTLING[color][castlingType][0],
		SQUARES_FOR_KING_CASTLING[color][castlingType][2]),
	_rookStart(SQUARES_FOR_ROOK_CASTLING[color][castlingType][0]),
	_rookDest(SQUARES_FOR_ROOK_CASTLING[color][castlingType][1])
{}

Square MoveCastle::getRookStart()
{
	return _rookStart;
}

Square MoveCastle::getRookDest()
{
	return _rookDest;
}

void MoveCastle::execute(
	std::function<void(Square, Square)> copySquare,
	std::function<void(ChessPiece, Square)> setAtPos,
	std::function<void(Square)> delAtPos)
{
	Move::execute(copySquare, setAtPos, delAtPos);
	copySquare(_rookStart, _rookDest);
	delAtPos(_rookStart);
}

BitBoard MoveCastle::getBBWithMoveDone()
{
	throw "ERROR. A Caslting Move does not produce a Move Bitboard";
}