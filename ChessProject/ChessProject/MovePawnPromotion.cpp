#include "MovePawnPromotion.h"

MovePawnPromotion::MovePawnPromotion() : Move()
{
	promotionType = PieceType::NoType;
}

MovePawnPromotion::MovePawnPromotion(Coordinate* givenStart, Coordinate* givenDestination, PieceType givenPromotionType)
	:Move(givenStart, givenDestination)
{
	promotionType = givenPromotionType;
}

PieceType MovePawnPromotion::getPromotionType()
{
	return promotionType;
}
