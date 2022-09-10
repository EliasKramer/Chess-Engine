#include "Game.h"

Game::Game(std::unique_ptr<Player>&& player1, std::unique_ptr<Player>&& player2)
	: _player1(std::move(player1)),
	_player2(std::move(player2)),
	_board(STARTING_FEN)
{}

void Game::start()
{
	while (true)
	{
		std::cout << _board.getString();
		UniqueMoveList legalMoves = _board.getAllLegalMoves();
		int choosenMoveIdx = _player1.get()->getMove(_board, legalMoves);
		Move* moveToMake = legalMoves.at(choosenMoveIdx).get();
	
		//TODO check if movelist inclues move
		_board.makeMove(moveToMake);
		
		std::cout << _board.getString();
		legalMoves = _board.getAllLegalMoves();
		choosenMoveIdx = _player1.get()->getMove(_board, legalMoves);
		moveToMake = legalMoves.at(choosenMoveIdx).get();

		//TODO check if movelist inclues move
		_board.makeMove(moveToMake);
	}
}
