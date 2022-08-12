#include "DataAndTypes.h"

ChessColor getColorOfFenChar(char c, std::string errorMsgPrefix)
{
	return isUpperCase(c) ? White :
		isLowerCase(c) ? Black :
		throw errorMsgPrefix + " Could not convert Char to Color";
}

CastlingType getCastlingTypeOfFenChar(char c, std::string errorMsgPrefix)
{
	if (isUpperCase(c))
	{
		c = charToLower(c);
	}
	return c == 'q' ? CastleLong :
		c == 'k' ? CastleShort :
		throw errorMsgPrefix + " Could not convert Char to CastlingType";
}

Square getSquareFromString(
	std::string str,
	std::string errorMsgPrefix)
{
	if (str == "-")
	{
		return SQUARE_NONE;
	}
	else if (str.size() == 2)
	{
		int file = str[0] - 'a';
		int rank = str[1] - '1';

		int idx = (Square)(file + (rank * 8));

		if (idx >= 0 && idx < 64)
		{
			return (Square)idx;
		}
	}
	throw errorMsgPrefix + " Could not convert String to Square";
}