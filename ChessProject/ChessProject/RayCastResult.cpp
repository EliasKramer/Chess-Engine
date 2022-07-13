#include "RayCastResult.h"

RayCastResult::RayCastResult()
{
	_isUnderAttack = false;
	_rayCastMoves = std::list<Move>();
}

RayCastResult::RayCastResult(bool isUnderAttack, std::list<Move> rayCastMoves)
{
	_isUnderAttack = isUnderAttack;
	_rayCastMoves = rayCastMoves;
}

bool RayCastResult::getIsUnderAttack()
{
	return _isUnderAttack;
}

std::list<Move> RayCastResult::getRayCastMoves()
{
	return _rayCastMoves;
}

void RayCastResult::setIsUnderAttack(bool value)
{
	_isUnderAttack = value;
}

void RayCastResult::setRayCastMoves(std::list<Move> value)
{
	_rayCastMoves = value;
}

void RayCastResult::addRayCastMove(Move* value)
{
	_rayCastMoves.push_back(*value);
}
