#include "MovePawnPromontion.h"

MovePawnPromontion::MovePawnPromontion()
{
    promotionType = PieceType::NoType;
}

MovePawnPromontion::MovePawnPromontion(PieceType givenType)
{
	promotionType = givenType;
}

PieceType MovePawnPromontion::getPromotionType()
{
    return promotionType;
}
