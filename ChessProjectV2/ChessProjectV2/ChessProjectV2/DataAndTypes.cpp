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
