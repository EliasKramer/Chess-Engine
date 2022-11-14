#include "SortedAlphaBetaPruningBot.h"

int SortedAlphaBetaPruningBot::get_move(
	const ChessBoard& board,
	const MoveList& moves)
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
		"Minimax with sorted Alpha Beta Pruning",
		nodes_searched,
		end_points_evaluated,
		depth,
		moves[best_move_idx],
		best_move_score,
		duration,
		additional_info);

	return best_move_idx;
}

bool SortedAlphaBetaPruningBot::is_capture_move(
	const Move& move,
	const ChessBoard& board) const
{
	//this doesnt include en passant captures
	return bitboards_overlap(board.get_board_representation().all_pieces, BB_SQUARE[move.get_destination()]);
}

int SortedAlphaBetaPruningBot::get_value_of_move_for_sorting(
	const Move& givenMove,
	const ChessBoard& board)
{
	//if there is no piece at start the move is not valid
	if (!bitboards_overlap(board.get_board_representation().all_pieces, BB_SQUARE[givenMove.get_start()]))
	{
		throw "Could not give this a Piece Value. It is either not a capture move or it is invalid";
	}
	//if there is no enemy at the destination spot - skip
	if (!bitboards_overlap(board.get_board_representation().all_pieces, BB_SQUARE[givenMove.get_destination()]))
	{
		return 0;
	}

	const BoardRepresentation board_rep = board.get_board_representation();
	
	const PieceType start_piece = board_rep.get_piece_at(givenMove.get_start()).get_type();
	const PieceType destination_piece = board_rep.get_piece_at(givenMove.get_destination()).get_type();

	if (destination_piece == king)
	{
		throw "No move should be able to capture a king";
	}

	//is high if you take a queen with a pawn, but is lower the other way around
	return PIECETYPE_VALUE[destination_piece] - PIECETYPE_VALUE[start_piece];
}

void SortedAlphaBetaPruningBot::parital_insertion_sort(
	MoveList& list,
	const ChessBoard& board)
{
	std::vector<int> evaluation_values = std::vector<int>();
	for (const Move& move : list)
	{
		evaluation_values.insert(evaluation_values.begin(), get_value_of_move_for_sorting(move, board));
	}

	for (int i = 1; i < list.size(); i++)
	{
		if (!is_capture_move(list[i], board))
		{
			continue;
		}
		//is no capture move - cannot be given a value

		int j = i;
		while (j > 0 && evaluation_values[j] > evaluation_values[j-1])
		{
			std::swap(list[j], list[j - 1]);
			std::swap(evaluation_values[j], evaluation_values[j - 1]);
			j--;
		}
	}
}

int SortedAlphaBetaPruningBot::get_move_score_recursively(
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
		int bestEval = is_maximizing_player ? INT_MIN : INT_MAX;

		parital_insertion_sort(moves, board);

		for (const Move& curr : moves)
		{
			ChessBoard copyBoard = board.get_copy_by_value();
			copyBoard.make_move(curr);

			nodes_searched++;
			int evaluation =
				get_move_score_recursively(
					copyBoard,
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
				bestEval = std::max(bestEval, evaluation);
				alpha = std::max(alpha, evaluation);
				if (beta <= alpha)
				{
					pruned_branches++;
					break;
				}
			}
			else
			{
				bestEval = std::min(bestEval, evaluation);
				beta = std::min(beta, evaluation);
				if (beta <= alpha)
				{
					pruned_branches++;
					break;
				}
			}
		}
		return bestEval;
	}
}
