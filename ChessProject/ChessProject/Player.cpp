#include "Player.h"

Player::Player()
{}

Move* Player::getNextMove(std::vector<Move*> possibleMoves)
{
	throw "get next move called on base player class. not possible";
}
