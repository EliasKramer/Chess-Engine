#include <iostream>
#include "ChessBoard.h"
#include "../ChessTestV2/TestMethods.h"
#include <string>
#include <utility>
#include <vector>
#include "Game.h"
#include "HumanPlayer.h"
int main()
{
	Game game(
		std::make_unique<HumanPlayer>(),
		std::make_unique<HumanPlayer>()
	);

	game.start();
}