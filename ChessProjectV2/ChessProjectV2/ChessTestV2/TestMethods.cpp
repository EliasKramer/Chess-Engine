#include "TestMethods.h"

bool moveListContains(Move m, const MoveList& moves)
{
	for (const Move& currMoveToCheck : moves)
	{
		if (currMoveToCheck == m)
		{
			return true;
		}
	}
	return false;
}

bool squaresBetweenAreSame(std::array<Square, MAX_SQUARES_BETWEEN> first, std::array<Square, MAX_SQUARES_BETWEEN> second)
{
	for(int i = 0; i < MAX_SQUARES_BETWEEN; i++)
	{
		if(first[i] != second[i])
		{
			return false;
		}
	}
	return true;
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
		for (const Move& curr : listOfMoves)
		{
			ChessBoard copyBoard = board.getCopyByValue();
			copyBoard.makeMove(curr);

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
		for (const Move& curr : listOfMoves)
		{
			ChessBoard copyBoard = board.getCopyByValue();
			copyBoard.makeMove(curr);

			for (Move& currMoveToAdd :
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
	for (const Move& curr : moves)
	{
		if (curr.getFlag() == EnPassant)
		{
			retVal++;
		}
	}
	return retVal;
}

int getNumberOfPromotionMoves(const MoveList& moves)
{
	int retVal = 0;
	for (const Move& curr : moves)
	{
		if (curr.getFlag() == PromoteQueen ||
			curr.getFlag() == PromoteRook ||
			curr.getFlag() == PromoteBishop ||
			curr.getFlag() == PromoteKnight)
		{
			retVal++;
		}
	}
	return retVal;
}

int getNumberOfCastlingMoves(const MoveList& moves)
{
	int retVal = 0;
	for (const Move& curr : moves)
	{
		if (curr.getFlag() == Castle)
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
		for (Move& currMoveToAdd : listOfMoves)
		{
			std::string stringToAdd =
				currStr
				+ SQUARE_STRING[currMoveToAdd.getStart()] + "->"
				+ SQUARE_STRING[currMoveToAdd.getDestination()] + ", ";

			listOfStringMoves.push_back(stringToAdd);
		}
		return listOfStringMoves;
	}
	else
	{
		std::vector<std::string> listOfStringMoves = {};
		for (const Move& curr : listOfMoves)
		{
			ChessBoard copyBoard = board.getCopyByValue();
			copyBoard.makeMove(curr);

			std::string currMoveString = currStr
				+ SQUARE_STRING[curr.getStart()] + "->"
				+ SQUARE_STRING[curr.getDestination()] + ", ";

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

	for (const Move& curr : listOfMoves)
	{
		ChessBoard copyBoard = board.getCopyByValue();
		copyBoard.makeMove(curr);

		//TODO replace with getString
		std::string currMoveString =
			SQUARE_STRING[curr.getStart()]
			+ SQUARE_STRING[curr.getDestination()];

		std::pair<std::string, int> currItem =
			std::make_pair(currMoveString, numberOfMovesAfterDepth(copyBoard, depth - 1));

		result.push_back(currItem);
	}
	return result;
}