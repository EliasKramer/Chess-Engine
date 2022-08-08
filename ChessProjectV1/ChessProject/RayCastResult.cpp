#include "RayCastResult.h"
#include <vector>

RayCastResult::RayCastResult():
	_rayCastMoves(std::vector<std::unique_ptr<Move>>())
{}

RayCastResult::RayCastResult(
	std::vector<std::unique_ptr<Move>>&& rayCastMoves
)//: _rayCastMoves(rayCastMoves)
{
	_rayCastMoves.insert(
		_rayCastMoves.end(),
		std::make_move_iterator(rayCastMoves.begin()),
		std::make_move_iterator(rayCastMoves.end()));
}

void RayCastResult::calculateIfIsUnderAttack(
	PieceType type,
	std::function<ChessPiece(Coordinate, Move*)> getPieceAt,
	Move imaginaryMove)
{
	
	for (std::unique_ptr<Move>& move : _rayCastMoves)
	{
		if (move->isValid())
		{
			Coordinate dest = move->getDestination();
			ChessPiece p = getPieceAt(dest, &imaginaryMove);
			if (p.getType() == type)
			{
				_isUnderAttack = true;
			}
		}
	}
}

bool RayCastResult::originPieceIsUnderAttack()
{
	return _isUnderAttack;
}

std::vector<std::unique_ptr<Move>> RayCastResult::getRayCastMoves()
{
	std::vector<std::unique_ptr<Move>> result;
	result.insert(
		result.end(),
		std::make_move_iterator(_rayCastMoves.begin()),
		std::make_move_iterator(_rayCastMoves.end()));

	return result;//;//_rayCastMoves;
}

void RayCastResult::combineWithOther(RayCastResult other)
{
	_rayCastMoves.insert(
		_rayCastMoves.end(),
		std::make_move_iterator(other._rayCastMoves.begin()),
		std::make_move_iterator(other._rayCastMoves.end()));

	_isUnderAttack = _isUnderAttack || other._isUnderAttack;
}