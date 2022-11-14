#include "Player.h"

Player::Player(std::string name)
    :_name(name)
{}

std::string Player::get_name()
{
    return _name;
}

int Player::get_move(
    const ChessBoard& board,
    const MoveList& moves)
{
    throw "Cannot call Player Base method";
}