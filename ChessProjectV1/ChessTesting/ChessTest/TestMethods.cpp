#include "TestMethods.h"
bool containsMove(const std::vector<std::unique_ptr<Move>>& list, Move x)
{
	for (const std::unique_ptr<Move>& move : list)
	{
		if(*move == x)
		{
			return true;
		}
	}
	return false;
}

int getRecursivelyAllMovesForBoard(int depth, ChessColor currColor, ChessBoardTest& board)
{
	if (depth == 0)
	{
		throw "no depths under 1 allowed";
	}
	if (depth == 1)
	{
		return board.getAllMoves(currColor).size();
	}
	else 
	{
		int allMovesCount = 0;
		for (std::unique_ptr<Move>& move : board.getAllMoves(currColor))
		{
			ChessBoardTest copiedBoard = board.getCopy();

			copiedBoard.executeMove(move.get());
			
			allMovesCount += getRecursivelyAllMovesForBoard(
				depth - 1,
				getOppositeColor(currColor),
				copiedBoard);
		}
		return allMovesCount;
	}
}
