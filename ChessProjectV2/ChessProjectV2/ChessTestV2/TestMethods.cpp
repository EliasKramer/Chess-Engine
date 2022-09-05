#include "TestMethods.h"

bool moveListContains(Move m, const UniqueMoveList& moves)
{
	for (const std::unique_ptr<Move>& currMoveToCheck : moves)
	{
		if (*currMoveToCheck == m)
		{
			return true;
		}
	}
	return false;
}

int numberOfMovesAfterDepth(ChessBoard& board, int depth)
{
	UniqueMoveList listOfMoves = board.getAllLegalMoves();
	if (depth == 1)
	{
		return listOfMoves.size();
	}
	else if (depth == 0)
	{
		return 1;
	}
	else
	{
		int allMovesCount = 0;
		for (const std::unique_ptr<Move>& curr : listOfMoves)
		{
			ChessBoard copyBoard = board.getCopyByValue();
			copyBoard.makeMove(curr.get());

			allMovesCount += numberOfMovesAfterDepth(copyBoard, depth - 1);
		}
		return allMovesCount;
	}
}
