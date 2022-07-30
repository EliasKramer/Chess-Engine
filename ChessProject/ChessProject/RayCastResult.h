#pragma once
#include "Move.h"
#include <vector>
#include <functional>
class RayCastResult
{
private:
	//all destinations are the fields, that hit the raycast
	std::vector<Move*> _rayCastMoves;

	//if the raycast-start-field is under attack
	bool _isUnderAttack = false;

	friend RayCastResult operator+ (const RayCastResult& first, const RayCastResult& second);
public:
	RayCastResult();
	RayCastResult(std::vector<Move*> rayCastMoves);

	void calculateIfIsUnderAttack(
		PieceType type,
		std::function<ChessPiece(Coordinate*, Move*)> getPieceAt,
		Move move);
	
	// you have to caluclate if it is under attack before.
	bool originPieceIsUnderAttack();
	// get all fields that the raycast hit.
	// the move list will be made out of the origin field of the raycast
	// and each hit field of the raycast as destination.
	std::vector<Move*> getRayCastMoves();
};
RayCastResult operator+ (const RayCastResult& first, const RayCastResult& second);