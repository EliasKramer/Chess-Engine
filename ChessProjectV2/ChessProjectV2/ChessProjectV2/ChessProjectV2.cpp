#include <iostream>
#include "ChessBoard.h"
#include "../ChessTestV2/TestMethods.h"
#include <string>
#include <utility>
#include <vector>
#include "Game.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
int main()
{
	Game game(
		std::make_unique<RandomPlayer>(),
		std::make_unique<RandomPlayer>()
	);

	game.start();
}