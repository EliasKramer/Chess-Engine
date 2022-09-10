#pragma once
#include "Player.h"
#include <memory>
#include <iostream>

class Game
{
private:
	std::unique_ptr<Player> _player1;
	std::unique_ptr<Player> _player2;

	ChessBoard _board;
public:
	Game(std::unique_ptr<Player>&& player1, std::unique_ptr<Player>&& player2);
	
	void start();
};