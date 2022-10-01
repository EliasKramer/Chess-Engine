#include "Medicrius.h"

Medicrius::Medicrius()
	:Player("Medicrus")
{}

Medicrius::Medicrius(std::string name)
	:Player(name)
{}

int Medicrius::getMove(const ChessBoard& board, const UniqueMoveList& moves)
{
	//multithreading would also be useful here

	auto begin = std::chrono::high_resolution_clock::now();

	int endPointsEvaluated = 0;
	int nodesSearched = 0;

	int depth = 3;

	int bestMoveScore = INT_MIN;
	int bestMoveIdx = 0;

	int moveIdx = 0;
	for (const std::unique_ptr<Move>& curr : moves)
	{
		ChessBoard boardCopy = board;
		boardCopy.makeMove(*curr);

		int currScore = getMoveRecursively(boardCopy, depth - 1, nodesSearched, endPointsEvaluated);

		if (currScore > bestMoveScore)
		{
			bestMoveScore = currScore;
			bestMoveIdx = moveIdx;
		}

		moveIdx++;
	}

	auto end = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

	std::cout
		<< "Medicrius searched " << nodesSearched << " nodes and "
		<< endPointsEvaluated << " end states are evaluated. "
		<< "It took " << duration << "ms" << std::endl;

	return bestMoveIdx;
}

int Medicrius::evaluateBoard(const ChessBoard& board)
{
	//regulates how much the material (the pieces on the board) is worth

	BoardRepresentation boardRep = board.getBoardRepresentation();

	//get the obvious out the way 
	// - if white wins return highest possible number
	// - if black wins return lowest possible number
	// - stalemate and draw is 0
	int gameStatePoints = GAME_STATE_EVALUATION[board.getGameState()];
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
		for (int typeIdx = 0; typeIdx <= Queen; typeIdx++)
		{
			//if current square overlaps with the current piece type
			if (bitboardsOverlap(idxBB, boardRep.PiecesOfType[typeIdx]))
			{
				//get the material value of the piece type
				int materialValue = PIECETYPE_VALUE[typeIdx];

				bool currPieceIsBlack = bitboardsOverlap(idxBB, boardRep.PiecesOfColor[Black]);
				ChessColor currPieceColor = currPieceIsBlack ? Black : White;

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
		(POSITION_VALUE_KING[White][board.getGameDurationState()][boardRep.KingPos[White]] -
			POSITION_VALUE_KING[Black][board.getGameDurationState()][boardRep.KingPos[Black]]);

	//TODO
	//to encourage pawns for more structure, it would be useful to look if they get protected
	//by another pawn. and increase the value if it is that way

	return score;
}

int Medicrius::getMoveRecursively(
	ChessBoard board,
	int depth,
	int& nodesSearched,
	int& endStatesSearched)
{
	if (depth == 0)
	{
		endStatesSearched++;
		return evaluateBoard(board);
	}
	else
	{
		UniqueMoveList moves = board.getAllLegalMoves();
		int bestEvaluationFound = INT_MIN;

		for (std::unique_ptr<Move>& curr : moves)
		{
			ChessBoard copyBoard = board.getCopyByValue();
			copyBoard.makeMove(*curr);
			
			nodesSearched++;
			int evaluation = -getMoveRecursively(copyBoard, depth - 1, nodesSearched, endStatesSearched);

			if (evaluation > bestEvaluationFound)
			{
				bestEvaluationFound = evaluation;
			}
		}

		//no more moves - get eval (can be improve by only checking what king is under attack)
		if (bestEvaluationFound == INT_MIN)
		{
			endStatesSearched++;
			return evaluateBoard(board);
		}

		return bestEvaluationFound;
	}
	//has to return index
}