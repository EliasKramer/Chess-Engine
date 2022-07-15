#include "RayCastResult.h"
#include <vector>

RayCastResult::RayCastResult()
{
	_isUnderAttack = false;
	_rayCastMoves = std::vector<Move>();
}

RayCastResult::RayCastResult(bool isUnderAttack, std::vector<Move> rayCastMoves)
{
	_isUnderAttack = isUnderAttack;
	_rayCastMoves = rayCastMoves;
}

bool RayCastResult::getIsUnderAttack()
{
	return _isUnderAttack;
}

std::vector<Move> RayCastResult::getRayCastMoves()
{
	return _rayCastMoves;
}

void RayCastResult::setIsUnderAttack(bool value)
{
	_isUnderAttack = value;
}

void RayCastResult::setRayCastMoves(std::vector<Move> value)
{
	_rayCastMoves = value;
}

void RayCastResult::addRayCastMove(Move* value)
{
	_rayCastMoves.push_back(*value);
}

RayCastResult operator+(const RayCastResult& first, const RayCastResult& second)
{
	std::vector<Move> first_moves = first._rayCastMoves;
	std::vector<Move> second_moves = second._rayCastMoves;

	first_moves.insert(
		first_moves.end(),
		second_moves.begin(),
		second_moves.end());

	return RayCastResult(
		first._isUnderAttack || second._isUnderAttack,
		first_moves
	);

	return RayCastResult();
}
