#include "BitBoard.h"

const std::array<BitBoard, 64> BB_SQUARE = []()->std::array<BitBoard, 64> {
	std::array<BitBoard, 64> retVal = {};

	for (int i = A1; i <= H8; i++)
	{
		retVal[i] = 1ULL << i;
	}

	return retVal;
}();

bool operator!=(const Square first, const Square second)
{
	return (int)first == (int)second;
}

int getRankOfSquare(Square square)
{
	return square / 8;
}

int getFileOfSquare(Square square)
{
	return square % 8;
}

bool squaresAreOnTheSameFile(Square first, Square second)
{
	return
		getFileOfSquare(first) == getFileOfSquare(second);
}

bool squaresAreOnTheSameRank(Square first, Square second)
{
	return getRankOfSquare(first) == getRankOfSquare(second);
}

bool squaresAreOnTheSameDiagonal(Square first, Square second)
{
	return
		((first-second) % 7 == 0) || 
		((first-second) % 9 == 0);
}

bool destinationIsOnBoard(Square start, Direction direction)
{
	//if the invalid board for the direction and
	//the start square dont overlap then the new pos is valid
	return (INVALID_FIELDS_FOR_DIR.at(direction) & BB_SQUARE[start]) == 0;
}

bool squareOverlapsWithBB(Square pos, BitBoard bb)
{
	return (BB_SQUARE[pos] & bb) != 0ULL;
}

bool bitboardsOverlap(BitBoard first, BitBoard second)
{
	return (first & second) != 0ULL;
}

std::array<Square, MAX_SQUARES_BETWEEN> getSquaresBetween(
	Square start,
	Square end)
{
	std::array<Square, MAX_SQUARES_BETWEEN> result = 
	{SQUARE_NONE, SQUARE_NONE, SQUARE_NONE, SQUARE_NONE, SQUARE_NONE, SQUARE_NONE};
	
	if(start == end || start == SQUARE_NONE || end == SQUARE_NONE)
	{
		return result;
	}
	int startFile = getFileOfSquare(start);
	int startRank = getRankOfSquare(start);
	int endFile = getFileOfSquare(end);
	int endRank = getRankOfSquare(end);
	
	int fileDiff = endFile - startFile;
	int rankDiff = endRank - startRank;

	if (abs(fileDiff) <= 1 && abs(rankDiff) <= 1)
	{
		return result;
	}

	int rankDir = rankDiff == 0 ? 0 : rankDiff > 0 ? 1 : -1;
	int fileDir = fileDiff == 0 ? 0 : fileDiff > 0 ? 1 : -1;

	int rank = startRank + rankDir;
	int file = startFile + fileDir;

	int i = 0;
	while (!(rank == endRank && file == endFile))
	{
		result[i] = (Square)(rank * 8 + file);
		rank += rankDir;
		file += fileDir;
		i++;
	}

	return result;
}