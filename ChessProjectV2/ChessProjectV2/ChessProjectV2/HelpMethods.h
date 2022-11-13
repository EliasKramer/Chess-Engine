#pragma once
#include <string>
#include <vector>
#include "DataAndTypes.h"
#include "BitBoard.h"

std::vector<std::string> split_string(
	std::string inputString,
	char charToSplit);

bool is_upper_case(char c);
bool is_lower_case(char c);

char char_to_lower(char c);


ChessColor get_color_of_fen_char(
	char c,
	std::string errorMsgPrefix = "ERROR");

CastlingType get_castling_type_of_fen_char(
	char c,
	std::string errorMsgPrefix = "ERROR");

Square get_square_from_string(
	std::string str,
	std::string errorMsgPrefix = "ERROR");

Direction get_forward_for_color(ChessColor color);
Direction get_backward_for_color(ChessColor color);

ChessColor get_opposite_color(ChessColor color);

bool is_ray_type(PieceType type);