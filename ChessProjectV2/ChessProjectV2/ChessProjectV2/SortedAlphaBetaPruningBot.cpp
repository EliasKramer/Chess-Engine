#include "SortedAlphaBetaPruningBot.h"

int SortedAlphaBetaPruningBot::get_move(const ChessBoard& board, const MoveList& moves)
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
		"Minimax with sorted Alpha Beta Pruning",
		nodesSearched,
		endPointsEvaluated,
		depth,
		moves[bestMoveIdx],
		bestMoveScore,
		duration,
		additionalInfo);

	return bestMoveIdx;
}

bool SortedAlphaBetaPruningBot::is_capture_move(const Move& move, const ChessBoard& board) const
{
	//this doesnt include en passant captures
	return bitboards_overlap(board.get_board_representation().all_pieces, BB_SQUARE[move.getDestination()]);
}

int SortedAlphaBetaPruningBot::get_value_of_move_for_sorting(const Move& givenMove, const ChessBoard& board)
{
	//if there is no piece at start the move is not valid
	if (!bitboards_overlap(board.get_board_representation().all_pieces, BB_SQUARE[givenMove.getStart()]))
	{
		throw "Could not give this a Piece Value. It is either not a capture move or it is invalid";
	}
	//if there is no enemy at the destination spot - skip
	if (!bitboards_overlap(board.get_board_representation().all_pieces, BB_SQUARE[givenMove.getDestination()]))
	{
		return 0;
	}

	const BoardRepresentation boardRep = board.get_board_representation();
	
	const PieceType startPiece = boardRep.get_piece_at(givenMove.getStart()).get_type();
	const PieceType destinationPiece = boardRep.get_piece_at(givenMove.getDestination()).get_type();

	if (destinationPiece == king)
	{
		throw "No move should be able to capture a king";
	}

	//is high if you take a queen with a pawn, but is lower the other way around
	return PIECETYPE_VALUE[destinationPiece] - PIECETYPE_VALUE[startPiece];
}

void SortedAlphaBetaPruningBot::parital_insertion_sort(MoveList& list, const ChessBoard& board)
{
	std::vector<int> evaluatenValues = std::vector<int>();
	for (const Move& move : list)
	{
		evaluatenValues.insert(evaluatenValues.begin(), get_value_of_move_for_sorting(move, board));
	}

	for (int i = 1; i < list.size(); i++)
	{
		if (!is_capture_move(list[i], board))
		{
			continue;
		}
		//is no capture move - cannot be given a value

		int j = i;
		while (j > 0 && evaluatenValues[j] > evaluatenValues[j-1])
		{
			std::swap(list[j], list[j - 1]);
			std::swap(evaluatenValues[j], evaluatenValues[j - 1]);
			j--;
		}
	}
}

int SortedAlphaBetaPruningBot::get_move_score_recursively(ChessBoard board, int depth, bool isMaximizingPlayer, int alpha, int beta, int& nodesSearched, int& endStatesSearched, int& prunedBranches)
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

		parital_insertion_sort(moves, board);

		for (const Move& curr : moves)
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
