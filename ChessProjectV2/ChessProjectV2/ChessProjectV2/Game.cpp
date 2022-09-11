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
		ChessColor currentTurnColor = _board.getCurrentTurnColor();
		Player* currPlayer = currentTurnColor == White ? _player1.get() : _player2.get();

		int currentTurnNumber = _board.getNumberOfMovesPlayed();

		std::cout << "\n\n" << COLOR_STRING[currentTurnColor] << "s turn " << currentTurnNumber;
		std::cout << _board.getString();
		UniqueMoveList legalMoves = _board.getAllLegalMoves();
		int choosenMoveIdx = currPlayer->getMove(_board, legalMoves);
		if (choosenMoveIdx < 0 || choosenMoveIdx >= legalMoves.size())
		{
			throw "move cannot be executed. returned index is invalid!";
		}
		Move* moveToMake = legalMoves.at(choosenMoveIdx).get();
	
		_board.makeMove(moveToMake);

		GameState currGameState = _board.getGameState();
		if(currGameState == WhiteWon || currGameState == BlackWon)
		{
			std::cout << _board.getString();
			std::cout << "Checkmate! " << COLOR_STRING[currentTurnColor] << " wins!" << std::endl;
			break;
		}
		else if(currGameState == Draw)
		{
			std::cout << "Draw!" << std::endl;
			break;
		}
		else if(currGameState == Stalemate)
		{
			std::cout << "Stalemate!" << std::endl;
			break;
		}
	}
}