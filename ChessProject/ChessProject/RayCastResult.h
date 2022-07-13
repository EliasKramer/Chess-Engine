#pragma once
#include "Move.h"
#include <list>
class RayCastResult
{
private:
	//raycast ends in an opposite colored piece, that can attack you
	bool _isUnderAttack;
	//all destinations are the fields, that hit the raycast
	std::list<Move> _rayCastMoves;
public:
	RayCastResult();
	RayCastResult(bool isUnderAttack, std::list<Move> rayCastMoves);

	bool getIsUnderAttack();
	std::list<Move> getRayCastMoves();

	void setIsUnderAttack(bool value);
	void setRayCastMoves(std::list<Move> value);
	void addRayCastMove(Move* value);
};