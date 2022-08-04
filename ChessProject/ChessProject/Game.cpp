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

	ChessColor white = ChessColor::White;
	ChessColor black = ChessColor::Black;

	while (!gameOver)
	{
		std::cout << board.toString(ChessColor::White);

		std::cout << "White's turn" << std::endl;
		
		board.executeMove(playerWhite->getNextMove(board.getAllMoves(white)).get());
		//playerWhite->makeMove(board);
		
		std::cout << board.toString(ChessColor::Black);

		std::cout << "Black's turn" << std::endl;
		board.executeMove(playerWhite->getNextMove(board.getAllMoves(black)).get());

		//board.print();
		
		//gameOver = board.isGameOver();
		iterationCount++;

		gameOver = iterationCount >= 15;
	}
}
