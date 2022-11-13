#include "HelpMethods.h"

std::vector<std::string> split_string(
	std::string inputString,
	char charToSplit)
{
	std::vector<std::string> splittedString;
	std::string tempString;
	for (int i = 0; i < inputString.size(); i++)
	{
		if (inputString[i] == charToSplit)
		{
			if (tempString != "")
			{
				splittedString.push_back(tempString);
			}
			tempString.clear();
		}
		else
		{
			tempString.push_back(inputString[i]);
		}
	}
	splittedString.push_back(tempString);
	return splittedString;
}

bool is_upper_case(char c)
{
	return c >= 'A' && c <= 'Z';
}

bool is_lower_case(char c)
{
	return c >= 'a' && c <= 'z';
}

char char_to_lower(char c)
{
	return (c + ('a' - 'A'));
}

ChessColor get_color_of_fen_char(char c, std::string errorMsgPrefix)
{
	return is_upper_case(c) ? white :
		is_lower_case(c) ? black :
		throw errorMsgPrefix + " Could not convert Char to Color";
}

CastlingType get_castling_type_of_fen_char(char c, std::string errorMsgPrefix)
{
	if (is_upper_case(c))
	{
		c = char_to_lower(c);
	}
	return c == 'q' ? castle_long :
		c == 'k' ? castle_short :
		throw errorMsgPrefix + " Could not convert Char to CastlingType";
}

Square get_square_from_string(
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

Direction get_forward_for_color(ChessColor color)
{
	return color == white ? NORTH : SOUTH;
}

Direction get_backward_for_color(ChessColor color)
{
	return color == white ? SOUTH : NORTH;
}

ChessColor get_opposite_color(ChessColor color)
{
	return (ChessColor)((color + 1) % 2);
}

bool is_ray_type(PieceType type)
{
	return type == rook || type == bishop || type == queen;
}