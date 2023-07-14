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
	ChessGame game(
		std::make_unique<AlphaBetaPruningBot>(6),
		std::make_unique<AlphaBetaPruningBot>(6),
		STARTING_FEN
	);

	game.start();
}