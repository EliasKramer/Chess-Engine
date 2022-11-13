#include "Game.h"

Game::Game(
	std::unique_ptr<Player>&& player1,
	std::unique_ptr<Player>&& player2,
	std::string fen)
	: 
	_white_player(std::move(player1)),
	_black_player(std::move(player2)),
	_board(fen)
{}

void Game::start()
{
	//this variable stores all the moves of the players as the game progresses
	std::string movesMade = "";
	
	//this loop is the game loop
	//it will only end if the game is done
	while (true)
	{
		ChessColor currentTurnColor = _board.get_current_turn_color();
		Player& currPlayer = currentTurnColor == white ? *_white_player.get() : *_black_player.get();
		

		//this number increases every time black makes a move
		int currentTurnNumber = _board.get_number_of_moves_played();
		
		//print board and the move number
		std::cout 
			<< "\n\n" 
			<< COLOR_STRING[currentTurnColor] << " " << currPlayer.get_name() 
			<< "'s turn " << currentTurnNumber;
		std::cout << "\n" << (_board.get_game_duration_state() == MidGame ? "Mid Game" : "End Game");
		std::cout << "\n" << _board.get_fen();
		std::cout << _board.get_string();
		
		//get the move from the current player
		MoveList legalMoves = _board.get_all_legal_moves();
		//to make sure the move the player wants to play is legal, 
		//the return value is an index of the list of all legal moves
		int choosenMoveIdx = currPlayer.get_move(_board, legalMoves);
		//throws an error if the returned value is not a valid index
		if (choosenMoveIdx < 0 || choosenMoveIdx >= legalMoves.size())
		{
			throw "move cannot be executed. returned index is invalid!";
		}

		//get the move from the list
		Move& moveToMake = legalMoves.at(choosenMoveIdx);
		
		//store the current move and print it
		std::string currMoveStr = moveToMake.get_string();
		std::cout << "\n" << "move: " << currMoveStr << "\n";
		movesMade += currMoveStr + "\n";

		//execute the move
		_board.make_move(moveToMake);

		//get the gamestate and evaluate if the game has ended
		GameState currGameState = _board.get_game_state();
		if(currGameState == white_won || currGameState == black_won)
		{
			std::cout << _board.get_string();
			std::cout << "Checkmate! " << COLOR_STRING[currentTurnColor] << " wins!" << std::endl;
			break;
		}
		else if(currGameState == draw)
		{
			std::cout << "Draw!" << std::endl;
			break;
		}
		else if(currGameState == stalemate)
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