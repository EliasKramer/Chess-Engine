#include "Game.h"
#include <iostream>
Game::Game()
{}

Game::Game(
	std::unique_ptr<Player>&& givenWhitePlayer,
	std::unique_ptr<Player>&& givenBlackPlayer) 
	: 
	playerWhite(std::move(givenWhitePlayer)),
	playerBlack(std::move(givenBlackPlayer))
{}

void Game::start()
{
	bool gameOver = false;
	int iterationCount = 0;

	while (!gameOver)
	{
		std::cout << board.toString(ChessColor::White);

		std::cout << "White's turn" << std::endl;
		//playerWhite->makeMove(board);
		
		std::cout << board.toString(ChessColor::Black);

		std::cout << "Black's turn" << std::endl;
		//playerBlack->makeMove(board);
		
		//board.print();
		
		//gameOver = board.isGameOver();
		iterationCount++;

		gameOver = iterationCount >= 1;
	}
}
