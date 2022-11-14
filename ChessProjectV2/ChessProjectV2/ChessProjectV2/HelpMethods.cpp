#include "HelpMethods.h"

std::vector<std::string> split_string(
	std::string input_string,
	char char_to_split)
{
	std::vector<std::string> splitted_string;
	std::string temp_string;
	for (int i = 0; i < input_string.size(); i++)
	{
		if (input_string[i] == char_to_split)
		{
			if (temp_string != "")
			{
				splitted_string.push_back(temp_string);
			}
			temp_string.clear();
		}
		else
		{
			temp_string.push_back(input_string[i]);
		}
	}
	splitted_string.push_back(temp_string);
	return splitted_string;
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

ChessColor get_color_of_fen_char(char c, std::string error_msg_prefix)
{
	return is_upper_case(c) ? white :
		is_lower_case(c) ? black :
		throw error_msg_prefix + " Could not convert Char to Color";
}

CastlingType get_castling_type_of_fen_char(
	char c, 
	std::string error_msg_prefix)
{
	if (is_upper_case(c))
	{
		c = char_to_lower(c);
	}
	return c == 'q' ? castle_long :
		c == 'k' ? castle_short :
		throw error_msg_prefix + " Could not convert Char to CastlingType";
}

Square get_square_from_string(
	std::string str,
	std::string error_msg_prefix)
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
	throw error_msg_prefix + " Could not convert String to Square";
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