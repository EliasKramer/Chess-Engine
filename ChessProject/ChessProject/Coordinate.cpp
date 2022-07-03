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

char Coordinate::getFileNormal()
{
	return (char)(file + 'a');
}

short Coordinate::getRankNormal()
{
	return (unsigned short)(rank + 1);
}

short Coordinate::getFileAsPosition()
{
	return file;
}

short Coordinate::getRankAsPosition()
{
	return rank;
}

bool Coordinate::isValid()
{
	return file < BOARD_SIZE && file >= 0 &&
		rank < BOARD_SIZE && rank >= 0;
}

bool Coordinate::operator ==(const Coordinate& other) const
{
	return other.rank == rank && other.file == file;
}

bool Coordinate::operator!=(const Coordinate& other) const
{
	return !(operator ==(other));
}
