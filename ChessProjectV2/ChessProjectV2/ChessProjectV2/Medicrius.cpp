#include "Medicrius.h"

Medicrius::Medicrius()
	:Player("Medicrus")
{}

Medicrius::Medicrius(std::string name)
	:Player(name)
{}

int Medicrius::get_move(const ChessBoard& board, const MoveList& moves)
{
	//multithreading would also be useful here

	auto begin = std::chrono::high_resolution_clock::now();

	//needs to choose the greatest negative numbner if black
	bool is_white_to_move = board.get_current_turn_color() == white;
	int color_mult = is_white_to_move ? 1 : -1;

	int end_points_evaluated = 0;
	int nodes_searched = 0;

	int depth = 4;

	int best_move_score = INT_MIN;
	int best_move_idx = 0;

	int move_idx = 0;
	for (const Move curr : moves)
	{
		ChessBoard board_copy = board;
		board_copy.make_move(curr);

		int max_capture_depth_reached = 0;

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
				max_capture_depth_reached
			);

		int curr_score = color_mult * move_score;

		std::cout
			<< "Move: " << curr.get_string()
			<< ", Score: " << curr_score
			<< ", Max Capture Depth: " << max_capture_depth_reached
			<< ", Endstates Evaluated: " << end_points_evaluated - end_states_before
			<< std::endl;

		if (curr_score > best_move_score)
		{
			best_move_score = curr_score;
			best_move_idx = move_idx;
		}

		move_idx++;
	}

	auto end = std::chrono::high_resolution_clock::now();

	long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

	print_search_statistics("Minimax with alpha beta pruning", nodes_searched, end_points_evaluated, depth, moves[best_move_idx], best_move_score, duration);

	return best_move_idx;
}

int Medicrius::evaluate_board(const ChessBoard& board)
{
	//regulates how much the material (the pieces on the board) is worth

	BoardRepresentation board_rep = board.get_board_representation();

	//get the obvious out the way 
	// - if white wins return highest possible number
	// - if black wins return lowest possible number
	// - stalemate and draw is 0
	int game_state_points = GAME_STATE_EVALUATION[board.get_game_state()];
	//if the game is still ongoing the value will be -1 and thus should be continued evaluating
	if (game_state_points != -1)
	{
		//if the game is already over return the evaluation
		return game_state_points;
	}

	//now calculate the score
	int score = 0;

	for (int i = A1; i <= H8; i++)
	{
		BitBoard index_BB = BB_SQUARE[i];

		//iterate over every type except king
		for (int type_idx = 0; type_idx <= queen; type_idx++)
		{
			//if current square overlaps with the current piece type
			if (bitboards_overlap(index_BB, board_rep.pieces_of_type[type_idx]))
			{
				//get the material value of the piece type
				int material_value = PIECETYPE_VALUE[type_idx];

				bool curr_piece_is_black = bitboards_overlap(index_BB, board_rep.pieces_of_color[black]);
				ChessColor curr_piece_color = curr_piece_is_black ? black : white;

				material_value += POSITION_VALUE[curr_piece_color][type_idx][i];

				//if pieces are black, negate the value
				if (curr_piece_is_black)
				{
					material_value *= -1;
				}
				//add the value to the total score multiplied by material weight
				score += material_value;
			}
		}
	}

	//Evaluating the king position
	//usually the king is worth 20k and the position value is added to that.
	//this is not done here, since these values cancel out. - could be done for clarity
	score +=
		(POSITION_VALUE_KING[white][board.get_game_duration_state()][board_rep.king_pos[white]] -
			POSITION_VALUE_KING[black][board.get_game_duration_state()][board_rep.king_pos[black]]);

	//TODO
	//to encourage pawns for more structure, it would be useful to look if they get protected
	//by another pawn. and increase the value if it is that way

	return score;
}

void Medicrius::print_search_statistics(
	std::string method_used,
	int nodes_searched,
	int end_states_evaluated,
	int depth,
	const Move& selected_move,
	int score,
	long long time_elapsed,
	std::string additional_info
)
{
	double nodes_per_second = ((double)nodes_searched / ((double)time_elapsed / 1000));
	double end_states_per_second = ((double)end_states_evaluated / ((double)time_elapsed / 1000));
	std::cout
		<< "---------------------------------------" << std::endl
		<< "Medicrius searched with Method: " << method_used << std::endl << std::endl
		<< "Searched " << nodes_searched << " nodes in depth " << depth << std::endl
		<< "Evaluated " << end_states_evaluated << " end states. " << std::endl
		<< "Time elapsed: " << time_elapsed << "ms" << std::endl
		<< additional_info << std::endl
		<< "Nodes per second: " << nodes_per_second << std::endl
		<< "End states per second: " << end_states_per_second << std::endl
		<< "Selected move: " << selected_move.get_string() << std::endl
		<< "Score: " << score << ". " << std::endl
		<< "---------------------------------------" << std::endl;

}

int Medicrius::get_move_score_recursively(
	ChessBoard board,
	int depth,
	bool is_maximizing_player,
	int alpha,
	int beta,
	int& nodes_searched,
	int& end_states_searched,
	int& max_capture_depth_reached)
{
	if (depth == 0)
	{
		end_states_searched++;
		nodes_searched++;
		/*
		int currCaptureMovesDepth = 0;
		int allCaptureMovesValue =
			-get_all_capture_moves_score_recursively(
				board,
				-alpha,
				-beta,
				nodes_searched,
				end_states_searched,
				currCaptureMovesDepth);

		//std::cout << "Max depth: " << currCaptureMovesDepth << std::endl;
		max_capture_depth_reached = std::max(max_capture_depth_reached, currCaptureMovesDepth);
		return allCaptureMovesValue;*/
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
					max_capture_depth_reached);

			if (is_maximizing_player)
			{
				best_eval = std::max(best_eval, evaluation);
				alpha = std::max(alpha, evaluation);
				if (beta <= alpha)
				{
					break;
				}
			}
			else
			{
				best_eval = std::min(best_eval, evaluation);
				beta = std::min(beta, evaluation);
				if (beta <= alpha)
				{
					break;
				}
			}
		}
		return best_eval;
	}
}

int Medicrius::get_all_capture_moves_score_recursively(
	ChessBoard board,
	bool is_maximizing_player,
	int alpha,
	int beta,
	int& nodes_searched,
	int& end_states_searched,
	int& max_depth_reached,
	int curr_depth)
{
	MoveList possible_captures = board.get_all_legal_capture_moves();

	if (possible_captures.size() == 0)
	{
		nodes_searched++;
		end_states_searched++;
		max_depth_reached = std::max(max_depth_reached, curr_depth);
		return evaluate_board(board);
	}

	int best_evaluation_found = INT_MIN;

	for (Move curr : possible_captures)
	{
		ChessBoard copy_board = board.get_copy_by_value();
		copy_board.make_move(curr);

		nodes_searched++;
		int evaluation =
			-get_all_capture_moves_score_recursively(
				copy_board,
				!is_maximizing_player,
				-alpha,
				-beta,
				nodes_searched,
				end_states_searched,
				max_depth_reached,
				curr_depth + 1);

		if (evaluation > best_evaluation_found)
		{
			best_evaluation_found = evaluation;
		}
	}

	return best_evaluation_found;
}