#pragma once
#include <string>
class Coordinate
{
private:
	short file;
	short rank;
public:
	Coordinate();
	Coordinate(char givenFile, short givenRank);
	Coordinate(short givenFile, short givenRank);
	//used for board position as known
	char getFileNormal();
	short getRankNormal();
	//used for array position
	short getFileAsPosition();
	short getRankAsPosition();
	//is on an 8x8 chess board
	bool isValid();

	std::string toString();

	bool operator ==(const Coordinate& other) const;
	bool operator !=(const Coordinate& other) const;
};