#pragma once

#include "Move.h"
class MovePawnPromontion : Move
{
private: 
	PieceType promotionType;
public:
	MovePawnPromontion();
	MovePawnPromontion(PieceType givenType);
	PieceType getPromotionType();
};