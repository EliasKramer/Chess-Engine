#include "Coordinate.h"
#include "MetaData.h"
Coordinate::Coordinate()
{
	file = -1;
	rank = -1;
}
Coordinate::Coordinate(char givenFile, short givenRank)
{
	file = (givenFile - 'a');
	rank = (givenRank - 1);
}

Coordinate::Coordinate(short givenFile, short givenRank)
{
	file = givenFile;
	rank = givenRank;
}

//chess coordinate based file
char Coordinate::getFileNormal()
{
	return (char)(file + 'a');
}

//chess coordinate based rank
short Coordinate::getRankNormal()
{
	return (unsigned short)(rank + 1);
}

//0 based file for arrays
short Coordinate::getFileAsPosition()
{
	return file;
}
//0 based rank for arrays
short Coordinate::getRankAsPosition()
{
	return rank;
}

bool Coordinate::isValid()
{
	return file < BOARD_SIZE && file >= 0 &&
		rank < BOARD_SIZE && rank >= 0;
}

std::string Coordinate::toString()
{
	std::string retVal = std::to_string(getFileNormal());
	retVal += std::to_string((int)getRankNormal());

	return retVal;
}

bool Coordinate::operator ==(const Coordinate& other) const
{
	return other.rank == rank && other.file == file;
}

bool Coordinate::operator!=(const Coordinate& other) const
{
	return !(operator ==(other));
}