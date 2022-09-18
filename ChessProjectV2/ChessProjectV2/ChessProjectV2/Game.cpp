#include "Game.h"

Game::Game(std::unique_ptr<Player>&& player1, std::unique_ptr<Player>&& player2)
	: _player1(std::move(player1)),
	_player2(std::move(player2)),
	_board(STARTING_FEN)
{}

void Game::start()
{
	//this variable stores all the moves of the players as the game progresses
	std::string movesMade = "";
	
	//this loop is the game loop
	//it will only end if the game is done
	while (true)
	{
		ChessColor currentTurnColor = _board.getCurrentTurnColor();
		Player* currPlayer = currentTurnColor == White ? _player1.get() : _player2.get();

		//this number increases every time black makes a move
		int currentTurnNumber = _board.getNumberOfMovesPlayed();
		
		//print board and the move number
		std::cout << "\n\n" << COLOR_STRING[currentTurnColor] << "s turn " << currentTurnNumber;
		std::cout << _board.getString();
		
		//get the move from the current player
		UniqueMoveList legalMoves = _board.getAllLegalMoves();
		//to make sure the move the player wants to play is legal, 
		//the return value is an index of the list of all legal moves
		int choosenMoveIdx = currPlayer->getMove(_board, legalMoves);
		//throws an error if the returned value is not a valid index
		if (choosenMoveIdx < 0 || choosenMoveIdx >= legalMoves.size())
		{
			throw "move cannot be executed. returned index is invalid!";
		}

		//get the move from the list
		Move& moveToMake = *legalMoves.at(choosenMoveIdx).get();
		
		//store the current move and print it
		std::string currMoveStr = moveToMake.getString();
		std::cout << "\n" << "move: " << currMoveStr << "\n";
		movesMade += currMoveStr + "\n";

		//execute the move
		_board.makeMove(moveToMake);

		//get the gamestate and evaluate if the game has ended
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

	//print the history of moves
	std::cout << "\n\nPress any key to show move log\n";
	system("pause");
	std::cout << "Moves made:\n" << movesMade;
}