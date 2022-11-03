#include <iostream>
#include "Game.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
#include "Medicrius.h"
#include "UnoptimizedMinimaxBot.h"
#include "AlphaBetaPruningBot.h"
#include "SortedAlphaBetaPruningBot.h"
int main()
{
	Game game(
		std::make_unique<SortedAlphaBetaPruningBot>(),
		std::make_unique<AlphaBetaPruningBot>()
	);

	game.start();
}