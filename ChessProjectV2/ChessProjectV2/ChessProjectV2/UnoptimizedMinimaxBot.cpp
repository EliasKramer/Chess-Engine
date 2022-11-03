#include "UnoptimizedMinimaxBot.h"

int UnoptimizedMinimaxBot::getMove(const ChessBoard& board, const MoveList& moves)
{
	//multithreading would also be useful here

	const auto begin = std::chrono::high_resolution_clock::now();

	//needs to choose the greatest negative numbner if black
	const int colorMult = board.getCurrentTurnColor() == White ? 1 : -1;

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
	for (const std::unique_ptr<Move>& curr : moves)
	{
		ChessBoard boardCopy = board;
		boardCopy.makeMove(*curr);

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

	printSearchStatistics(
		"Pure Minimax", 
		nodesSearched, 
		endPointsEvaluated,
		depth,
		*moves[bestMoveIdx].get(), 
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
		return evaluateBoard(board);
	}
	else
	{
		MoveList moves = board.getAllLegalMoves();

		//no more moves
		if (moves.size() == 0)
		{
			nodesSearched++;
			endStatesSearched++;
			return board.isKingInCheck() ?
				(board.getCurrentTurnColor() == White ?
					//when the depth is very high, the checkmate can be done earlier
					//(when you search with depth 4, the function gets called with 3, 2, 1, 0 recursively)
					//therefore a higher depth in the argument means actually low depth.
					////finding a checkmate at a low depth is better, because it can be delivered earlier
					GAME_STATE_EVALUATION[BlackWon] - depth :
					GAME_STATE_EVALUATION[WhiteWon] + depth)
				: 0;
		}
		int bestEval = INT_MIN;
		for (std::unique_ptr<Move>& curr : moves)
		{
			ChessBoard copyBoard = board.getCopyByValue();
			copyBoard.makeMove(*curr);

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