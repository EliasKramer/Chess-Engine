#pragma once
#include<memory>
#include "Player.h"
#include "ChessBoard.h"
class Game
{
private:
	std::unique_ptr<Player> playerWhite;
	std::unique_ptr<Player> playerBlack;

	ChessBoard board;

public:
	Game();
	Game(std::unique_ptr<Player>&& givenWhitePlayer,
		std::unique_ptr<Player>&& givenBlackPlayer);

	void start();
};