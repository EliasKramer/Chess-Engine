#pragma once
#include "MetaData.h"
#include <functional>
#include "ChessPiece.h"
#include "Coordinate.h"
#include "Move.h"

class MovePawnPromotion : public Move
{
private:
	PieceType promotionType;
public:
	MovePawnPromotion();
	MovePawnPromotion(
		Coordinate* givenStart,
		Coordinate* givenDestination,
		PieceType givenPromotionType);

	void execute(
		std::function<ChessPiece(Coordinate*)> getAtPosition,
		std::function<void(ChessPiece*, Coordinate*)> setPieceAt) override;

	PieceType getPromotionType();
};