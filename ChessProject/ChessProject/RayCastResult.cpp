#include "RayCastResult.h"
#include <vector>

bool RayCastResult::checkIfDestinationInMovesIsTheSameType(
	PieceType* type,
	std::function<ChessPiece(Coordinate*, Move*)> getPieceAt,
	Move* imaginaryMove)
{
	for (Move move : _rayCastMoves)
	{
		if (move.isValid())
		{
			Coordinate dest = move.getDestination();
			ChessPiece p = getPieceAt(&dest, imaginaryMove);
			if (p.getType() == *type)
			{
				return true;
			}
		}
	}
	return false;
}

RayCastResult::RayCastResult()
{
	_rayCastMoves = std::vector<Move>();
}

RayCastResult::RayCastResult(std::vector<Move> rayCastMoves)
{
	_rayCastMoves = rayCastMoves;
}

void RayCastResult::calculateIfIsUnderAttack(
	PieceType* type,
	std::function<ChessPiece(Coordinate*, Move*)> getPieceAt,
	Move* move)
{
	_isUnderAttack = checkIfDestinationInMovesIsTheSameType(type, getPieceAt, move);
}

void RayCastResult::calculateIfIsUnderAttack(
	std::vector<PieceType*> types,
	std::function<ChessPiece(Coordinate*, Move*)> getPieceAt,
	Move* move)
{
	bool result = false;
	for (PieceType* type : types)
	{
		result = result || checkIfDestinationInMovesIsTheSameType(type, getPieceAt, move);
	}
	_isUnderAttack = result;
}

bool RayCastResult::originPieceIsUnderAttack()
{
	return _isUnderAttack;
}

std::vector<Move> RayCastResult::getRayCastMoves()
{
	return _rayCastMoves;
}

RayCastResult operator+(const RayCastResult& first, const RayCastResult& second)
{
	std::vector<Move> first_moves = first._rayCastMoves;
	std::vector<Move> second_moves = second._rayCastMoves;

	first_moves.insert(
		first_moves.end(),
		second_moves.begin(),
		second_moves.end());

	RayCastResult result = RayCastResult(first_moves);
	result._isUnderAttack = first._isUnderAttack || second._isUnderAttack;

	return result;
}