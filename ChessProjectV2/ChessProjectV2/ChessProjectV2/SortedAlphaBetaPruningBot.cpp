#include "SortedAlphaBetaPruningBot.h"

int SortedAlphaBetaPruningBot::getMove(const ChessBoard& board, const UniqueMoveList& moves)
{
	auto begin = std::chrono::high_resolution_clock::now();

	bool isWhiteToMove = board.getCurrentTurnColor() == White;
	int colorMult = isWhiteToMove ? 1 : -1;

	int endPointsEvaluated = 0;
	int nodesSearched = 0;
	int branchesPruned = 0;

	int depth = 5;

	int bestMoveScore = INT_MIN;
	int bestMoveIdx = 0;

	int moveIdx = 0;
	for (const std::unique_ptr<Move>& curr : moves)
	{
		ChessBoard boardCopy = board;
		boardCopy.makeMove(*curr);

		int endstatesBefore = endPointsEvaluated;

		int moveScore =
			getMoveScoreRecursively(
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
			<< "Move: " << curr.get()->getString()
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

	printSearchStatistics(
		"Minimax with sorted Alpha Beta Pruning",
		nodesSearched,
		endPointsEvaluated,
		depth,
		*moves[bestMoveIdx].get(),
		bestMoveScore,
		duration,
		additionalInfo);

	return bestMoveIdx;
}

int SortedAlphaBetaPruningBot::getValueOfMoveForSorting(const Move& givenMove, const ChessBoard& board)
{
	//if there is no piece at start the move is not valid
	if (!bitboardsOverlap(board.getBoardRepresentation().AllPieces, BB_SQUARE[givenMove.getStart()]))
	{
		throw "Could not give this a Piece Value. It is either not a capture move or it is invalid";
	}
	//if there is no enemy at the destination spot - skip
	if (!bitboardsOverlap(board.getBoardRepresentation().AllPieces, BB_SQUARE[givenMove.getDestination()]))
	{
		return 0;
	}

	const BoardRepresentation boardRep = board.getBoardRepresentation();
	
	const PieceType startPiece = boardRep.getPieceAt(givenMove.getStart()).getType();
	const PieceType destinationPiece = boardRep.getPieceAt(givenMove.getDestination()).getType();

	if (destinationPiece == King)
	{
		throw "No move should be able to capture a king";
	}

	//is high if you take a queen with a pawn, but is lower the other way around
	return PIECETYPE_VALUE[destinationPiece] - PIECETYPE_VALUE[startPiece];
}

bool SortedAlphaBetaPruningBot::compareMoves(const Move m1, const Move m2)
{
	return false;
}

int SortedAlphaBetaPruningBot::getMoveScoreRecursively(ChessBoard board, int depth, bool isMaximizingPlayer, int alpha, int beta, int& nodesSearched, int& endStatesSearched, int& prunedBranches)
{
	if (depth == 0)
	{
		endStatesSearched++;
		nodesSearched++;
		return evaluateBoard(board);
	}
	else
	{
		UniqueMoveList moves = board.getAllLegalMoves();

		//no more moves
		if (moves.size() == 0)
		{
			nodesSearched++;
			endStatesSearched++;
			//dont know if this works
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
		int bestEval = isMaximizingPlayer ? INT_MIN : INT_MAX;
		
		std::vector<int> testList = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		std::sort(testList.begin(), testList.end(), compareMoves);

		for (std::unique_ptr<Move>& curr : moves)
		{
			ChessBoard copyBoard = board.getCopyByValue();
			copyBoard.makeMove(*curr);

			nodesSearched++;
			int evaluation =
				getMoveScoreRecursively(
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
