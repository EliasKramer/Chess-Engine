#include "AlphaBetaPruningBot.h"

int AlphaBetaPruningBot::get_move(const ChessBoard& board, const MoveList& moves)
{
	auto begin = std::chrono::high_resolution_clock::now();

	bool is_white_to_move = board.get_current_turn_color() == white;
	int color_mult = is_white_to_move ? 1 : -1;

	int end_points_evaluated = 0;
	int nodes_searched = 0;
	int branches_pruned = 0;

	int depth = 5;

	int best_move_score = INT_MIN;
	int best_move_idx = 0;

	int curr_move_idx = 0;
	for (const Move& curr : moves)
	{
		ChessBoard board_copy = board;
		board_copy.make_move(curr);

		int end_states_before = end_points_evaluated;

		int move_score =
			get_move_score_recursively(
				board_copy,
				depth - 1,
				!is_white_to_move,
				BLACK_WIN_EVAL_VALUE,
				WHITE_WIN_EVAL_VALUE,
				nodes_searched,
				end_points_evaluated,
				branches_pruned
			);

		int curr_score = color_mult * move_score;

		
		std::cout
			<< "Move: " << curr.get_string()
			<< ", Score: " << curr_score
			<< ", Endstates Evaluated: " << end_points_evaluated - end_states_before
			<< std::endl;
		

		if (curr_score > best_move_score)
		{
			best_move_score = curr_score;
			best_move_idx = curr_move_idx;
		}

		curr_move_idx++;
	}

	auto end = std::chrono::high_resolution_clock::now();

	long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

	std::string additional_info = "Pruned Branches: " + std::to_string(branches_pruned);
	
	print_search_statistics(
		"Minimax with Alpha Beta Pruning",
		nodes_searched,
		end_points_evaluated,
		depth,
		moves[best_move_idx],
		best_move_score,
		duration,
		additional_info);

	return best_move_idx;
}

int AlphaBetaPruningBot::get_move_score_recursively(
	ChessBoard board,
	int depth,
	bool is_maximizing_player,
	int alpha,
	int beta,
	int& nodes_searched,
	int& end_states_searched,
	int& pruned_branches)
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
			//dont know if this works
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
		int best_eval = is_maximizing_player ? INT_MIN : INT_MAX;
		for (Move curr : moves)
		{
			ChessBoard copy_board = board.get_copy_by_value();
			copy_board.make_move(curr);

			nodes_searched++;
			int evaluation =
				get_move_score_recursively(
					copy_board,
					depth - 1,
					!is_maximizing_player,
					-alpha,
					-beta,
					nodes_searched,
					end_states_searched,
					pruned_branches
				);

			if (is_maximizing_player)
			{
				best_eval = std::max(best_eval, evaluation);
				alpha = std::max(alpha, evaluation);
				if (beta <= alpha)
				{
					pruned_branches++;
					break;
				}
			}
			else
			{
				best_eval = std::min(best_eval, evaluation);
				beta = std::min(beta, evaluation);
				if (beta <= alpha)
				{
					pruned_branches++;
					break;
				}
			}
		}
		return best_eval;
	}
}