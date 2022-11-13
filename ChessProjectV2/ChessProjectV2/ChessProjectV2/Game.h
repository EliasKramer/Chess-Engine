#pragma once
#include "Player.h"
#include <memory>
#include <iostream>
#include <string>
class Game
{
private:
	std::unique_ptr<Player> _white_player;
	std::unique_ptr<Player> _black_player;

	ChessBoard _board;
public:
	Game(
		std::unique_ptr<Player>&& player1,
		std::unique_ptr<Player>&& player2,
		std::string fen = STARTING_FEN);

	void start();
};