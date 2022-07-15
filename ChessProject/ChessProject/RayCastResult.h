#pragma once
#include "Move.h"
#include <vector>
class RayCastResult
{
private:
	//raycast ends in an opposite colored piece, that can attack you
	bool _isUnderAttack;
	//all destinations are the fields, that hit the raycast
	std::vector<Move> _rayCastMoves;
	
	friend RayCastResult operator+ (const RayCastResult& first, const RayCastResult& second);
public:
	RayCastResult();
	RayCastResult(bool isUnderAttack, std::vector<Move> rayCastMoves);

	bool getIsUnderAttack();
	std::vector<Move> getRayCastMoves();

	void setIsUnderAttack(bool value);
	void setRayCastMoves(std::vector<Move> value);

	void addRayCastMove(Move* value);

	//gets the lastest raycast hit and if the piece there is the same type 
	//as the given argument, it is considered attacked
	void updateIsUnderAttack(PieceType* type, ChessPiece (*getPieceAt)(Coordinate*));
};
RayCastResult operator+ (const RayCastResult& first, const RayCastResult& second);