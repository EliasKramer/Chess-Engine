#pragma once
#include "Move.h"
#include "MetaData.h"
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
	PieceType getPromotionType();
};