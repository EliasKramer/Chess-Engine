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
		std::make_unique<SortedAlphaBetaPruningBot>(),
		std::make_unique<AlphaBetaPruningBot>(),
		"r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
	);

	game.start();
}