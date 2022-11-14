#pragma once

#include "../../ChessProjectV2/ChessProjectV2/Move.h"
#include "../../ChessProjectV2/ChessProjectV2/ChessBoard.h"
#include <vector>
#include <string>
#include <utility>

bool move_list_contains(Move m, const MoveList& moves);
bool squares_between_are_same(
	std::array<Square, MAX_SQUARES_BETWEEN> first,
	std::array<Square, MAX_SQUARES_BETWEEN> second);

int number_of_moves_after_depth(const ChessBoard& board, int depth);

MoveList get_all_moves_at_depth(const ChessBoard& board, int depth);
int get_number_of_en_passant_moves(const MoveList& moves);
int get_number_of_promotion_moves(const MoveList& moves);
int get_number_of_castling_moves(const MoveList& moves);

std::vector<std::string> get_all_move_strings_at_depth(
	const ChessBoard& board,
	std::string curr_string,
	int depth);
std::vector<std::pair<std::string, int>> get_number_of_moves_after_first_move(
	const ChessBoard& board,
	int depth);