#include "AlphaBetaPruningBot.h"

int AlphaBetaPruningBot::get_move(const ChessBoard& board, const MoveList& moves)
{
	auto begin = std::chrono::high_resolution_clock::now();

	bool isWhiteToMove = board.get_current_turn_color() == white;
	int colorMult = isWhiteToMove ? 1 : -1;

	int endPointsEvaluated = 0;
	int nodesSearched = 0;
	int branchesPruned = 0;

	int depth = 5;

	int bestMoveScore = INT_MIN;
	int bestMoveIdx = 0;

	int moveIdx = 0;
	for (const Move& curr : moves)
	{
		ChessBoard boardCopy = board;
		boardCopy.make_move(curr);

		int endstatesBefore = endPointsEvaluated;

		int moveScore =
			get_move_score_recursively(
				boardCopy,
				depth - 1,
				!isWhiteToMove,
				BLACK_WIN_EVAL_VALUE,
				WHITE_WIN_EVAL_VALUE,
				nodesSearched,
				endPointsEvaluated,
				branchesPruned
			);

		int currScore = colorMult * moveScore;

		
		std::cout
			<< "Move: " << curr.get_string()
			<< ", Score: " << currScore
			<< ", Endstates Evaluated: " << endPointsEvaluated - endstatesBefore
			<< std::endl;
		

		if (currScore > bestMoveScore)
		{
			bestMoveScore = currScore;
			bestMoveIdx = moveIdx;
		}

		moveIdx++;
	}

	auto end = std::chrono::high_resolution_clock::now();

	long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

	std::string additionalInfo = "Pruned Branches: " + std::to_string(branchesPruned);
	
	print_search_statistics(
		"Minimax with Alpha Beta Pruning",
		nodesSearched,
		endPointsEvaluated,
		depth,
		moves[bestMoveIdx],
		bestMoveScore,
		duration,
		additionalInfo);

	return bestMoveIdx;
}

int AlphaBetaPruningBot::get_move_score_recursively(
	ChessBoard board,
	int depth,
	bool isMaximizingPlayer,
	int alpha,
	int beta,
	int& nodesSearched,
	int& endStatesSearched,
	int& prunedBranches)
{
	if (depth == 0)
	{
		endStatesSearched++;
		nodesSearched++;
		return evaluate_board(board);
	}
	else
	{
		MoveList moves = board.get_all_legal_moves();

		//no more moves
		if (moves.size() == 0)
		{
			nodesSearched++;
			endStatesSearched++;
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
		int bestEval = isMaximizingPlayer ? INT_MIN : INT_MAX;
		for (Move curr : moves)
		{
			ChessBoard copyBoard = board.get_copy_by_value();
			copyBoard.make_move(curr);

			nodesSearched++;
			int evaluation =
				get_move_score_recursively(
					copyBoard,
					depth - 1,
					!isMaximizingPlayer,
					-alpha,
					-beta,
					nodesSearched,
					endStatesSearched,
					prunedBranches
				);

			if (isMaximizingPlayer)
			{
				bestEval = std::max(bestEval, evaluation);
				alpha = std::max(alpha, evaluation);
				if (beta <= alpha)
				{
					prunedBranches++;
					break;
				}
			}
			else
			{
				bestEval = std::min(bestEval, evaluation);
				beta = std::min(beta, evaluation);
				if (beta <= alpha)
				{
					prunedBranches++;
					break;
				}
			}
		}
		return bestEval;
	}
}