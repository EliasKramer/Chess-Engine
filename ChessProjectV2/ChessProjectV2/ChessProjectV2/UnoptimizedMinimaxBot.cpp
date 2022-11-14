#include "UnoptimizedMinimaxBot.h"

int UnoptimizedMinimaxBot::get_move(
	const ChessBoard& board,
	const MoveList& moves)
{
	//multithreading would also be useful here

	const auto begin = std::chrono::high_resolution_clock::now();

	//needs to choose the greatest negative numbner if black
	const int color_mult = board.get_current_turn_color() == white ? 1 : -1;

	//every evaluated game state
	int end_points_evaluated = 0;
	//every game state that is found
	int nodes_searched = 0;

	//the depth to search to
	const int depth = 3;

	//the score of the current best move
	int best_move_score = INT_MIN;
	//the beste current move index of the given possible moves
	int best_move_idx = 0;
	
	//current move index
	int move_idx = 0;
	for (const Move& curr : moves)
	{
		ChessBoard board_copy = board;
		board_copy.make_move(curr);

		const int endstates_before = end_points_evaluated;

		const int moce_score =
			minimax(
				board_copy,
				depth - 1,
				nodes_searched,
				end_points_evaluated
			);

		const int curr_score = color_mult * moce_score;

		/*
		std::cout
			<< "Move: " << curr.get()->getString()
			<< ", Score: " << curr_score
			<< ", Endstates Evaluated: " << end_points_evaluated - endstates_before
			<< std::endl;
		*/

		if (curr_score > best_move_score)
		{
			best_move_score = curr_score;
			best_move_idx = move_idx;
		}

		move_idx++;
	}

	const auto end = std::chrono::high_resolution_clock::now();

	print_search_statistics(
		"Pure Minimax", 
		nodes_searched, 
		end_points_evaluated,
		depth,
		moves[best_move_idx], 
		best_move_score, 
		std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
	
	return best_move_idx;
}

int UnoptimizedMinimaxBot::minimax(
	ChessBoard board,
	int depth,
	int& nodes_searched,
	int& end_states_searched)
{
	if (depth == 0)
	{
		end_states_searched++;
		nodes_searched++;
		return evaluate_board(board);
	}
	else
	{
		MoveList moves = board.get_all_legal_moves();

		//no more moves
		if (moves.size() == 0)
		{
			nodes_searched++;
			end_states_searched++;
			return board.is_king_in_check() ?
				(board.get_current_turn_color() == white ?
					//when the depth is very high, the checkmate can be done earlier
					//(when you search with depth 4, the function gets called with 3, 2, 1, 0 recursively)
					//therefore a higher depth in the argument means actually low depth.
					////finding a checkmate at a low depth is better, because it can be delivered earlier
					GAME_STATE_EVALUATION[black_won] - depth :
					GAME_STATE_EVALUATION[white_won] + depth)
				: 0;
		}
		int best_eval = INT_MIN;
		for (Move& curr : moves)
		{
			ChessBoard copy_board = board.get_copy_by_value();
			copy_board.make_move(curr);

			nodes_searched++;
			int evaluation =
				-minimax(
					copy_board,
					depth - 1,
					nodes_searched,
					end_states_searched);

			if (evaluation > best_eval)
			{
				best_eval = evaluation;
			}
		}

		return best_eval;
	}
}