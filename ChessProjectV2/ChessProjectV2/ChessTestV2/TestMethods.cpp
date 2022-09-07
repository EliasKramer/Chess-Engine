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

int numberOfMovesAfterDepth(const ChessBoard& board, int depth)
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

UniqueMoveList getAllMovesAtDepth(const ChessBoard& board, int depth)
{
	UniqueMoveList listOfMoves = board.getAllLegalMoves();
	if (depth == 1)
	{
		return listOfMoves;
	}
	else
	{
		UniqueMoveList moves;
		for (const std::unique_ptr<Move>& curr : listOfMoves)
		{
			ChessBoard copyBoard = board.getCopyByValue();
			copyBoard.makeMove(curr.get());

			for (std::unique_ptr<Move>& currMoveToAdd :
				getAllMovesAtDepth(copyBoard, depth - 1))
			{
				moves.push_back(std::move(currMoveToAdd));
			}
		}
		return moves;
	}
}

int getNumberOfEnPassantMoves(const UniqueMoveList& moves)
{
	int retVal = 0;
	for (const std::unique_ptr<Move>& curr : moves)
	{
		if (dynamic_cast<MoveEnPassant*>(curr.get()))
		{
			retVal++;
		}
	}
	return retVal;
}

int getNumberOfPromotionMoves(const UniqueMoveList& moves)
{
	int retVal = 0;
	for (const std::unique_ptr<Move>& curr : moves)
	{
		if (dynamic_cast<MovePromote*>(curr.get()))
		{
			retVal++;
		}
	}
	return retVal;
}

int getNumberOfCastlingMoves(const UniqueMoveList& moves)
{
	int retVal = 0;
	for (const std::unique_ptr<Move>& curr : moves)
	{
		if (dynamic_cast<MoveCastle*>(curr.get()))
		{
			retVal++;
		}
	}
	return retVal;
}
