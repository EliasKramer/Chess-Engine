#include "TestMethods.h"
bool containsMove(const std::vector<Move*>& list, Move* x)
{
	//return false;
	for (Move* move : list)
	{
		if(*move == *x)
		{
			return true;
		}
	}
	return false;
	//return std::find(list.begin(), list.end(), x) != list.end();
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
		for (Move* move : board.getAllMoves(currColor))
		{
			ChessBoardTest copiedBoard = board.getCopy();

			copiedBoard.executeMove(move);
			
			allMovesCount += getRecursivelyAllMovesForBoard(
				depth - 1,
				getOppositeColor(currColor),
				copiedBoard);
		}
		return allMovesCount;
	}
}
