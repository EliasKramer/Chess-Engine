#include <iostream>
#include "ChessBoard.h"
#include "../ChessTestV2/TestMethods.h"
#include <string>
#include <utility>
#include <vector>
#include "Game.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
#include "Medicrius.h"
#include "UnoptimizedMinimaxBot.h"
int main()
{
	Game game(
		std::make_unique<RandomPlayer>(),
		std::make_unique<UnoptimizedMinimaxBot>()
	);

	game.start();
}