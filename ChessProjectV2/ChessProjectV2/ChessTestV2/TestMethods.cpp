#include "TestMethods.h"

bool move_list_contains(Move m, const MoveList& moves)
{
	for (const Move& curr_move_to_check : moves)
	{
		if (curr_move_to_check == m)
		{
			return true;
		}
	}
	return false;
}

bool squares_between_are_same(
	std::array<Square, MAX_SQUARES_BETWEEN> first,
	std::array<Square, MAX_SQUARES_BETWEEN> second)
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

int number_of_moves_after_depth(const ChessBoard& board, int depth)
{
	MoveList list_of_moves = board.get_all_legal_moves();
	if (depth == 1)
	{
		return list_of_moves.size();
	}
	else if (depth == 0)
	{
		return 1;
	}
	else
	{
		int all_moves_count = 0;
		for (const Move& curr : list_of_moves)
		{
			ChessBoard copy_board = board.get_copy_by_value();
			copy_board.make_move(curr);

			all_moves_count += number_of_moves_after_depth(copy_board, depth - 1);
		}
		return all_moves_count;
	}
}

MoveList get_all_moves_at_depth(const ChessBoard& board, int depth)
{
	MoveList list_of_moves = board.get_all_legal_moves();
	if (depth == 1)
	{
		return list_of_moves;
	}
	else
	{
		MoveList moves;
		for (const Move& curr : list_of_moves)
		{
			ChessBoard copy_board = board.get_copy_by_value();
			copy_board.make_move(curr);

			for (Move& curr_move_to_add :
				get_all_moves_at_depth(copy_board, depth - 1))
			{
				moves.push_back(std::move(curr_move_to_add));
			}
		}
		return moves;
	}
}

int get_number_of_en_passant_moves(const MoveList& moves)
{
	int ret_val = 0;
	for (const Move& curr : moves)
	{
		if (curr.get_flag() == en_passant)
		{
			ret_val++;
		}
	}
	return ret_val;
}

int get_number_of_promotion_moves(const MoveList& moves)
{
	int ret_val = 0;
	for (const Move& curr : moves)
	{
		if (curr.get_flag() == promote_queen ||
			curr.get_flag() == promote_rook ||
			curr.get_flag() == promote_bishop ||
			curr.get_flag() == promote_knight)
		{
			ret_val++;
		}
	}
	return ret_val;
}

int get_number_of_castling_moves(const MoveList& moves)
{
	int ret_val = 0;
	for (const Move& curr : moves)
	{
		if (curr.get_flag() == castle)
		{
			ret_val++;
		}
	}
	return ret_val;
}

std::vector<std::string> get_all_move_strings_at_depth(
	const ChessBoard& board, std::string curr_string, int depth)
{
	MoveList list_of_moves = board.get_all_legal_moves();
	if (depth == 1)
	{
		std::vector<std::string> list_of_string_moves = {};
		for (Move& curr_move_to_add : list_of_moves)
		{
			std::string stringToAdd =
				curr_string
				+ SQUARE_STRING[curr_move_to_add.get_start()] + "->"
				+ SQUARE_STRING[curr_move_to_add.get_destination()] + ", ";

			list_of_string_moves.push_back(stringToAdd);
		}
		return list_of_string_moves;
	}
	else
	{
		std::vector<std::string> list_of_string_moves = {};
		for (const Move& curr : list_of_moves)
		{
			ChessBoard copy_board = board.get_copy_by_value();
			copy_board.make_move(curr);

			std::string curr_move_string = curr_string
				+ SQUARE_STRING[curr.get_start()] + "->"
				+ SQUARE_STRING[curr.get_destination()] + ", ";

			std::vector<std::string> recursion =
				get_all_move_strings_at_depth(copy_board, curr_move_string, depth - 1);

			list_of_string_moves.insert(
				list_of_string_moves.end(),
				recursion.begin(),
				recursion.end()
			);
		}
		return list_of_string_moves;
	}
}

std::vector<std::pair<std::string, int>> get_number_of_moves_after_first_move(
	const ChessBoard& board,
	int depth)
{
	std::vector<std::pair<std::string, int>> result;

	MoveList list_of_moves = board.get_all_legal_moves();

	for (const Move& curr : list_of_moves)
	{
		ChessBoard copy_board = board.get_copy_by_value();
		copy_board.make_move(curr);

		//TODO replace with getString
		std::string curr_move_string =
			SQUARE_STRING[curr.get_start()]
			+ SQUARE_STRING[curr.get_destination()];

		std::pair<std::string, int> curr_item =
			std::make_pair(curr_move_string, number_of_moves_after_depth(copy_board, depth - 1));

		result.push_back(curr_item);
	}
	return result;
}