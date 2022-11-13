#include "UnoptimizedMinimaxBot.h"

int UnoptimizedMinimaxBot::get_move(const ChessBoard& board, const MoveList& moves)
{
	//multithreading would also be useful here

	const auto begin = std::chrono::high_resolution_clock::now();

	//needs to choose the greatest negative numbner if black
	const int colorMult = board.get_current_turn_color() == white ? 1 : -1;

	//every evaluated game state
	int endPointsEvaluated = 0;
	//every game state that is found
	int nodesSearched = 0;

	//the depth to search to
	const int depth = 3;

	//the score of the current best move
	int bestMoveScore = INT_MIN;
	//the beste current move index of the given possible moves
	int bestMoveIdx = 0;
	
	//current move index
	int moveIdx = 0;
	for (const Move& curr : moves)
	{
		ChessBoard boardCopy = board;
		boardCopy.make_move(curr);

		const int endstatesBefore = endPointsEvaluated;

		const int moveScore =
			minimax(
				boardCopy,
				depth - 1,
				nodesSearched,
				endPointsEvaluated
			);

		const int currScore = colorMult * moveScore;

		/*
		std::cout
			<< "Move: " << curr.get()->getString()
			<< ", Score: " << currScore
			<< ", Endstates Evaluated: " << endPointsEvaluated - endstatesBefore
			<< std::endl;
		*/

		if (currScore > bestMoveScore)
		{
			bestMoveScore = currScore;
			bestMoveIdx = moveIdx;
		}

		moveIdx++;
	}

	const auto end = std::chrono::high_resolution_clock::now();

	print_search_statistics(
		"Pure Minimax", 
		nodesSearched, 
		endPointsEvaluated,
		depth,
		moves[bestMoveIdx], 
		bestMoveScore, 
		std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
	
	return bestMoveIdx;
}

int UnoptimizedMinimaxBot::minimax(ChessBoard board, int depth, int& nodesSearched, int& endStatesSearched)
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
		int bestEval = INT_MIN;
		for (Move& curr : moves)
		{
			ChessBoard copyBoard = board.get_copy_by_value();
			copyBoard.make_move(curr);

			nodesSearched++;
			int evaluation =
				-minimax(
					copyBoard,
					depth - 1,
					nodesSearched,
					endStatesSearched);

			if (evaluation > bestEval)
			{
				bestEval = evaluation;
			}
		}

		return bestEval;
	}
}