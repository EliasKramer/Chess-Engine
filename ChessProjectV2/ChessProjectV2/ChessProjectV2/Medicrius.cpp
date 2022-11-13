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
	bool isWhiteToMove = board.get_current_turn_color() == white;
	int colorMult = isWhiteToMove ? 1 : -1;

	int endPointsEvaluated = 0;
	int nodesSearched = 0;

	int depth = 4;

	int bestMoveScore = INT_MIN;
	int bestMoveIdx = 0;

	int moveIdx = 0;
	for (const Move curr : moves)
	{
		ChessBoard boardCopy = board;
		boardCopy.make_move(curr);

		int maxCaptureDepthReached = 0;

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
				maxCaptureDepthReached
			);

		int currScore = colorMult * moveScore;

		std::cout
			<< "Move: " << curr.get_string()
			<< ", Score: " << currScore
			<< ", Max Capture Depth: " << maxCaptureDepthReached
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

	print_search_statistics("Minimax with alpha beta pruning", nodesSearched, endPointsEvaluated, depth, moves[bestMoveIdx], bestMoveScore, duration);

	return bestMoveIdx;
}

int Medicrius::evaluate_board(const ChessBoard& board)
{
	//regulates how much the material (the pieces on the board) is worth

	BoardRepresentation boardRep = board.get_board_representation();

	//get the obvious out the way 
	// - if white wins return highest possible number
	// - if black wins return lowest possible number
	// - stalemate and draw is 0
	int gameStatePoints = GAME_STATE_EVALUATION[board.get_game_state()];
	//if the game is still ongoing the value will be -1 and thus should be continued evaluating
	if (gameStatePoints != -1)
	{
		//if the game is already over return the evaluation
		return gameStatePoints;
	}

	//now calculate the score
	int score = 0;

	for (int i = A1; i <= H8; i++)
	{
		BitBoard idxBB = BB_SQUARE[i];

		//iterate over every type except king
		for (int typeIdx = 0; typeIdx <= queen; typeIdx++)
		{
			//if current square overlaps with the current piece type
			if (bitboards_overlap(idxBB, boardRep.pieces_of_type[typeIdx]))
			{
				//get the material value of the piece type
				int materialValue = PIECETYPE_VALUE[typeIdx];

				bool currPieceIsBlack = bitboards_overlap(idxBB, boardRep.pieces_of_color[black]);
				ChessColor currPieceColor = currPieceIsBlack ? black : white;

				materialValue += POSITION_VALUE[currPieceColor][typeIdx][i];

				//if pieces are black, negate the value
				if (currPieceIsBlack)
				{
					materialValue *= -1;
				}
				//add the value to the total score multiplied by material weight
				score += materialValue;
			}
		}
	}

	//Evaluating the king position
	//usually the king is worth 20k and the position value is added to that.
	//this is not done here, since these values cancel out. - could be done for clarity
	score +=
		(POSITION_VALUE_KING[white][board.get_game_duration_state()][boardRep.king_pos[white]] -
			POSITION_VALUE_KING[black][board.get_game_duration_state()][boardRep.king_pos[black]]);

	//TODO
	//to encourage pawns for more structure, it would be useful to look if they get protected
	//by another pawn. and increase the value if it is that way

	return score;
}

void Medicrius::print_search_statistics(
	std::string methodUsed,
	int nodesSearched,
	int endStatesEvaluated,
	int depth,
	const Move& selectedMove,
	int score,
	long long timeElapsed,
	std::string additionalInfo
)
{
	double nodesPerSecond = ((double)nodesSearched / ((double)timeElapsed / 1000));
	double endStatesPerSecond = ((double)endStatesEvaluated / ((double)timeElapsed / 1000));
	std::cout
		<< "---------------------------------------" << std::endl
		<< "Medicrius searched with Method: " << methodUsed << std::endl << std::endl
		<< "Searched " << nodesSearched << " nodes in depth " << depth << std::endl
		<< "Evaluated " << endStatesEvaluated << " end states. " << std::endl
		<< "Time elapsed: " << timeElapsed << "ms" << std::endl
		<< additionalInfo << std::endl
		<< "Nodes per second: " << nodesPerSecond << std::endl
		<< "End states per second: " << endStatesPerSecond << std::endl
		<< "Selected move: " << selectedMove.get_string() << std::endl
		<< "Score: " << score << ". " << std::endl
		<< "---------------------------------------" << std::endl;

}

int Medicrius::get_move_score_recursively(
	ChessBoard board,
	int depth,
	bool isMaximizingPlayer,
	int alpha,
	int beta,
	int& nodesSearched,
	int& endStatesSearched,
	int& maxCaptureDepthReached)
{
	if (depth == 0)
	{
		endStatesSearched++;
		nodesSearched++;
		/*
		int currCaptureMovesDepth = 0;
		int allCaptureMovesValue =
			-get_all_capture_moves_score_recursively(
				board,
				-alpha,
				-beta,
				nodesSearched,
				endStatesSearched,
				currCaptureMovesDepth);

		//std::cout << "Max depth: " << currCaptureMovesDepth << std::endl;
		maxCaptureDepthReached = std::max(maxCaptureDepthReached, currCaptureMovesDepth);
		return allCaptureMovesValue;*/
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
					maxCaptureDepthReached);

			if (isMaximizingPlayer)
			{
				bestEval = std::max(bestEval, evaluation);
				alpha = std::max(alpha, evaluation);
				if (beta <= alpha)
				{
					break;
				}
			}
			else
			{
				bestEval = std::min(bestEval, evaluation);
				beta = std::min(beta, evaluation);
				if (beta <= alpha)
				{
					break;
				}
			}
		}
		return bestEval;
	}
}

int Medicrius::get_all_capture_moves_score_recursively(
	ChessBoard board,
	bool isMaximizingPlayer,
	int alpha,
	int beta,
	int& nodesSearched,
	int& endStatesSearched,
	int& maxDepthReached,
	int currDepth)
{
	MoveList possibleCaptures = board.get_all_legal_capture_moves();

	if (possibleCaptures.size() == 0)
	{
		nodesSearched++;
		endStatesSearched++;
		maxDepthReached = std::max(maxDepthReached, currDepth);
		return evaluate_board(board);
	}

	int bestEvaluationFound = INT_MIN;

	for (Move curr : possibleCaptures)
	{
		ChessBoard copyBoard = board.get_copy_by_value();
		copyBoard.make_move(curr);

		nodesSearched++;
		int evaluation =
			-get_all_capture_moves_score_recursively(
				copyBoard,
				!isMaximizingPlayer,
				-alpha,
				-beta,
				nodesSearched,
				endStatesSearched,
				maxDepthReached,
				currDepth + 1);

		if (evaluation > bestEvaluationFound)
		{
			bestEvaluationFound = evaluation;
		}
	}

	return bestEvaluationFound;
}