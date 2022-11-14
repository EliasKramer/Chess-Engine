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
	std::string moves_made = "";
	
	//this loop is the game loop
	//it will only end if the game is done
	while (true)
	{
		ChessColor current_turn_color = _board.get_current_turn_color();
		Player& curr_player = current_turn_color == white ? *_white_player.get() : *_black_player.get();
		

		//this number increases every time black makes a move
		int current_turn_number = _board.get_number_of_moves_played();
		
		//print board and the move number
		std::cout 
			<< "\n\n" 
			<< COLOR_STRING[current_turn_color] << " " << curr_player.get_name() 
			<< "'s turn " << current_turn_number;
		std::cout << "\n" << (_board.get_game_duration_state() == MidGame ? "Mid Game" : "End Game");
		std::cout << "\n" << _board.get_fen();
		std::cout << _board.get_string();
		
		//get the move from the current player
		MoveList legal_moves = _board.get_all_legal_moves();
		//to make sure the move the player wants to play is legal, 
		//the return value is an index of the list of all legal moves
		int choosen_move_idx = curr_player.get_move(_board, legal_moves);
		//throws an error if the returned value is not a valid index
		if (choosen_move_idx < 0 || choosen_move_idx >= legal_moves.size())
		{
			throw "move cannot be executed. returned index is invalid!";
		}

		//get the move from the list
		Move& move_to_make = legal_moves.at(choosen_move_idx);
		
		//store the current move and print it
		std::string curr_move_string = move_to_make.get_string();
		std::cout << "\n" << "move: " << curr_move_string << "\n";
		moves_made += curr_move_string + "\n";

		//execute the move
		_board.make_move(move_to_make);

		//get the gamestate and evaluate if the game has ended
		GameState curr_game_state = _board.get_game_state();
		if(curr_game_state == white_won || curr_game_state == black_won)
		{
			std::cout << _board.get_string();
			std::cout << "Checkmate! " << COLOR_STRING[current_turn_color] << " wins!" << std::endl;
			break;
		}
		else if(curr_game_state == draw)
		{
			std::cout << "Draw!" << std::endl;
			break;
		}
		else if(curr_game_state == stalemate)
		{
			std::cout << "Stalemate!" << std::endl;
			break;
		}
	}

	//print the history of moves
	std::cout << "\n\nPress any key to show move log\n";
	system("pause");
	std::cout << "Moves made:\n" << moves_made;
}