#pragma once
class Coordinate
{
private:
	unsigned short file;
	unsigned short rank;
public:
	Coordinate(char givenFile, unsigned short givenRank);
	Coordinate(unsigned short givenFile, unsigned short givenRank);
	//used for board position as known
	char getFileNormal();
	unsigned short getRankNormal();
	//used for array position
	unsigned short getFileAsPosition();
	unsigned short getRankAsPosition();
	//is on an 8x8 chess board
	bool isValid();
	bool operator ==(const Coordinate& other) const;
};