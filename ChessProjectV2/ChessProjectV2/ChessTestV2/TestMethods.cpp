#include "TestMethods.h"

bool moveListContains(Move m, const MoveList& moves)
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
	MoveList listOfMoves = board.getAllLegalMoves();
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
			copyBoard.makeMove(*curr.get());

			allMovesCount += numberOfMovesAfterDepth(copyBoard, depth - 1);
		}
		return allMovesCount;
	}
}

MoveList getAllMovesAtDepth(const ChessBoard& board, int depth)
{
	MoveList listOfMoves = board.getAllLegalMoves();
	if (depth == 1)
	{
		return listOfMoves;
	}
	else
	{
		MoveList moves;
		for (const std::unique_ptr<Move>& curr : listOfMoves)
		{
			ChessBoard copyBoard = board.getCopyByValue();
			copyBoard.makeMove(*curr.get());

			for (std::unique_ptr<Move>& currMoveToAdd :
				getAllMovesAtDepth(copyBoard, depth - 1))
			{
				moves.push_back(std::move(currMoveToAdd));
			}
		}
		return moves;
	}
}

int getNumberOfEnPassantMoves(const MoveList& moves)
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

int getNumberOfPromotionMoves(const MoveList& moves)
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

int getNumberOfCastlingMoves(const MoveList& moves)
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

std::vector<std::string> getAllMoveStringsAtDepth(
	const ChessBoard& board, std::string currStr, int depth)
{
	MoveList listOfMoves = board.getAllLegalMoves();
	if (depth == 1)
	{
		std::vector<std::string> listOfStringMoves = {};
		for (std::unique_ptr<Move>& currMoveToAdd : listOfMoves)
		{
			std::string stringToAdd =
				currStr
				+ SQUARE_STRING[currMoveToAdd->getStart()] + "->"
				+ SQUARE_STRING[currMoveToAdd->getDestination()] + ", ";

			listOfStringMoves.push_back(stringToAdd);
		}
		return listOfStringMoves;
	}
	else
	{
		std::vector<std::string> listOfStringMoves = {};
		for (const std::unique_ptr<Move>& curr : listOfMoves)
		{
			ChessBoard copyBoard = board.getCopyByValue();
			copyBoard.makeMove(*curr.get());

			std::string currMoveString = currStr
				+ SQUARE_STRING[curr->getStart()] + "->"
				+ SQUARE_STRING[curr->getDestination()] + ", ";

			std::vector<std::string> recursion =
				getAllMoveStringsAtDepth(copyBoard, currMoveString, depth - 1);

			listOfStringMoves.insert(
				listOfStringMoves.end(),
				recursion.begin(),
				recursion.end()
			);
		}
		return listOfStringMoves;
	}
}

std::vector<std::pair<std::string, int>> getNumberOfMovesAfterFirstMove(const ChessBoard& board, int depth)
{
	std::vector<std::pair<std::string, int>> result;

	MoveList listOfMoves = board.getAllLegalMoves();

	for (const std::unique_ptr<Move>& curr : listOfMoves)
	{
		ChessBoard copyBoard = board.getCopyByValue();
		copyBoard.makeMove(*curr.get());

		//TODO replace with getString
		std::string currMoveString =
			SQUARE_STRING[curr->getStart()]
			+ SQUARE_STRING[curr->getDestination()];

		std::pair<std::string, int> currItem =
			std::make_pair(currMoveString, numberOfMovesAfterDepth(copyBoard, depth - 1));

		result.push_back(currItem);
	}
	return result;
}