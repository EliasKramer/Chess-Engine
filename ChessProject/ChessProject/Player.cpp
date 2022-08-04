#include "Player.h"

Player::Player()
{}

std::unique_ptr<Move> Player::getNextMove(std::vector<std::unique_ptr<Move>> possibleMoves)
{
	throw "get next move called on base player class. not possible";
}
