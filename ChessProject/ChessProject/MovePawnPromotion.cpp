#include "MovePawnPromotion.h"

MovePawnPromotion::MovePawnPromotion() : Move()
{
	promotionType = PieceType::NoType;
}

MovePawnPromotion::MovePawnPromotion(
	Coordinate givenStart,
	Coordinate givenDestination,
	PieceType givenPromotionType)
	: Move(givenStart, givenDestination), 
	promotionType(givenPromotionType)
{}

void MovePawnPromotion::execute(
	std::function<ChessPiece(Coordinate)> getAtPosition,
	std::function<void(ChessPiece, Coordinate)> setPieceAt)
{
	ChessPiece promotionPiece = 
		ChessPiece(promotionType, getAtPosition(start).getColor());
	setPieceAt(promotionPiece, destination);

	ChessPiece emptyPiece = ChessPiece();
	setPieceAt(emptyPiece, start);
}

PieceType MovePawnPromotion::getPromotionType()
{
	return promotionType;
}
