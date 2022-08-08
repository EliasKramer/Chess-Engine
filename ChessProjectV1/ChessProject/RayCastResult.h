#pragma once
#include "Move.h"
#include <vector>
#include <functional>
#include <memory>
class RayCastResult
{
private:
	//all destinations are the fields, that hit the raycast
	std::vector<std::unique_ptr<Move>> _rayCastMoves;

	//if the raycast-start-field is under attack
	bool _isUnderAttack = false;

public:
	RayCastResult();
	RayCastResult(std::vector<std::unique_ptr<Move>>&& rayCastMoves);

	void calculateIfIsUnderAttack(
		PieceType type,
		std::function<ChessPiece(Coordinate, Move*)> getPieceAt,
		Move move);
	
	// you have to caluclate if it is under attack before.
	bool originPieceIsUnderAttack();
	// get all fields that the raycast hit.
	// the move list will be made out of the origin field of the raycast
	// and each hit field of the raycast as destination.
	std::vector<std::unique_ptr<Move>> getRayCastMoves();

	//the combination process transfers all information from the argument to the current instance
	//the argument is useless after this operation
	void combineWithOther(RayCastResult other);
};