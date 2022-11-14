#include "ChessBoard.h"

bool ChessBoard::destination_is_same_color(Square start, Direction direction, ChessColor color) const
{
	int new_pos = (start + direction);

	if (new_pos < A1 || new_pos > H8)
	{
		return false;
	}

	return position_is_same_color((Square)new_pos, color);
}

bool ChessBoard::position_is_same_color(Square pos, ChessColor color) const
{
	return (_board.pieces_of_color[color] & BB_SQUARE[pos]) != 0;
}

void ChessBoard::add_if_destination_is_valid(MoveList& moves, Square start, Direction dir) const
{
	if (destination_is_on_board(start, dir))
	{
		if (!destination_is_same_color(start, dir, _current_turn_color))
		{
			moves.push_back(Move(start, (Square)(start + dir)));
		}
	}
}

void ChessBoard::add_if_destination_is_color(
	MoveList& moves,
	Square start,
	Direction dir,
	ChessColor color) const
{
	if (destination_is_on_board(start, dir))
	{
		Square new_pos = (Square)(start + dir);
		if (position_is_same_color(new_pos, color))
		{
			moves.push_back(Move(start, new_pos));
		}
	}
}

void ChessBoard::get_pawn_moves(MoveList& moves) const
{
	Direction forward = get_forward_for_color(_current_turn_color);
	BitBoard start_rank = _current_turn_color == white ? RANK_2 : RANK_7;

	for (uint8_t curr_square_idx = A1; curr_square_idx <= H8; curr_square_idx++)
	{
		Square curr_square = (Square)curr_square_idx;
		BitBoard piece_pos_BB = BB_SQUARE[curr_square_idx];

		//if the current square is a pawn and the same color
		if ((piece_pos_BB &
			_board.pieces_of_type[pawn] &
			_board.pieces_of_color[_current_turn_color]) != 0ULL)
		{
			//one move forward
			if (destination_is_on_board(curr_square, forward))
			{
				Square forward_pos = (Square)(curr_square + forward);
				BitBoard forward_pos_BB = BB_SQUARE[forward_pos];

				if ((forward_pos_BB & _board.all_pieces) == 0ULL)
				{
					add_pawn_move(moves, curr_square, forward_pos);
					//moves.push_back(Move(curr_square, forward_pos));
					//TODO
					//if move ends on promotion rank it should be a promotion move

					//two moves forward (only possible if one move is possible
					Square doubleForward = (Square)(forward_pos + forward);
					if ((piece_pos_BB & start_rank) != 0 &&
						destination_is_on_board(forward_pos, forward) &&
						(BB_SQUARE[doubleForward] & _board.all_pieces) == 0ULL)
					{
						moves.push_back(Move(curr_square, doubleForward));
					}
				}
			}

			//taking diagonal checks
			//this loop checks one time left and one time right
			Direction left_and_right[2] = { WEST, EAST };
			for (int i = 0; i < 2; i++)
			{
				Direction direction = (Direction)(left_and_right[i] + forward);
				ChessColor opponent_color = get_opposite_color(_current_turn_color);

				if (destination_is_same_color(curr_square, direction, opponent_color)
					&& destination_is_on_board(curr_square, direction))
				{
					add_pawn_move(moves, curr_square, (Square)(curr_square + direction));
				}
			}
		}
	}
}

void ChessBoard::get_knight_moves(MoveList& moves) const
{
	for (uint8_t curr_square_idx = A1; curr_square_idx <= H8; curr_square_idx++)
	{
		if ((BB_SQUARE[curr_square_idx] &
			_board.pieces_of_type[knight] &
			_board.pieces_of_color[_current_turn_color]) != 0ULL)
		{
			add_if_destination_is_valid(moves, (Square)curr_square_idx, NORTH_NORTH_EAST);
			add_if_destination_is_valid(moves, (Square)curr_square_idx, EAST_NORTH_EAST);
			add_if_destination_is_valid(moves, (Square)curr_square_idx, EAST_SOUTH_EAST);
			add_if_destination_is_valid(moves, (Square)curr_square_idx, SOUTH_SOUTH_EAST);
			add_if_destination_is_valid(moves, (Square)curr_square_idx, SOUTH_SOUTH_WEST);
			add_if_destination_is_valid(moves, (Square)curr_square_idx, WEST_SOUTH_WEST);
			add_if_destination_is_valid(moves, (Square)curr_square_idx, WEST_NORTH_WEST);
			add_if_destination_is_valid(moves, (Square)curr_square_idx, NORTH_NORTH_WEST);
		}
	}
}

void ChessBoard::get_bishop_moves(MoveList& moves) const
{
	const int number_of_directions = 4;
	Direction directions[number_of_directions] =
	{ NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST };

	for (uint8_t curr_square_idx = A1; curr_square_idx <= H8; curr_square_idx++)
	{
		if ((BB_SQUARE[curr_square_idx] &
			_board.pieces_of_type[bishop] &
			_board.pieces_of_color[_current_turn_color]) != 0ULL)
		{
			add_ray_moves(moves, (Square)curr_square_idx, directions, number_of_directions);
		}
	}

}

void ChessBoard::get_rook_moves(MoveList& moves) const
{
	const int number_of_directions = 4;
	Direction directions[number_of_directions] =
	{ NORTH, EAST, SOUTH, WEST };

	for (uint8_t curr_square_idx = A1; curr_square_idx <= H8; curr_square_idx++)
	{
		if ((BB_SQUARE[curr_square_idx] &
			_board.pieces_of_type[rook] &
			_board.pieces_of_color[_current_turn_color]) != 0ULL)
		{
			add_ray_moves(moves, (Square)curr_square_idx, directions, number_of_directions);
		}
	}
}

void ChessBoard::get_queen_moves(MoveList& moves) const
{
	const int number_of_directions = 8;
	Direction directions[number_of_directions] =
	{ NORTH, EAST, SOUTH, WEST, NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST };

	for (uint8_t curr_square_idx = A1; curr_square_idx <= H8; curr_square_idx++)
	{
		if ((BB_SQUARE[curr_square_idx] &
			_board.pieces_of_type[queen] &
			_board.pieces_of_color[_current_turn_color]) != 0ULL)
		{
			add_ray_moves(moves, (Square)curr_square_idx, directions, number_of_directions);
		}
	}
}

void ChessBoard::get_king_moves(MoveList& moves) const
{
	for (uint8_t curr_square_idx = A1; curr_square_idx <= H8; curr_square_idx++)
	{
		if ((BB_SQUARE[curr_square_idx] &
			_board.pieces_of_type[king] &
			_board.pieces_of_color[_current_turn_color]) != 0ULL)
		{
			add_if_destination_is_valid(moves, (Square)curr_square_idx, NORTH);
			add_if_destination_is_valid(moves, (Square)curr_square_idx, NORTH_EAST);
			add_if_destination_is_valid(moves, (Square)curr_square_idx, EAST);
			add_if_destination_is_valid(moves, (Square)curr_square_idx, SOUTH_EAST);
			add_if_destination_is_valid(moves, (Square)curr_square_idx, SOUTH);
			add_if_destination_is_valid(moves, (Square)curr_square_idx, SOUTH_WEST);
			add_if_destination_is_valid(moves, (Square)curr_square_idx, WEST);
			add_if_destination_is_valid(moves, (Square)curr_square_idx, NORTH_WEST);
		}
	}
}

void ChessBoard::add_pawn_move(MoveList& moves, Square start, Square dest) const
{
	BitBoard promotion_rank = _current_turn_color == white ? RANK_8 : RANK_1;

	if ((BB_SQUARE[dest] & promotion_rank) != 0ULL)
	{
		moves.push_back(Move(start, dest, _current_turn_color, MoveFlag::promote_queen));
		moves.push_back(Move(start, dest, _current_turn_color, MoveFlag::promote_rook));
		moves.push_back(Move(start, dest, _current_turn_color, MoveFlag::promote_bishop));
		moves.push_back(Move(start, dest, _current_turn_color, MoveFlag::promote_knight));
	}
	else
	{
		moves.push_back(Move(start, dest));
	}
}

void ChessBoard::get_castling_moves(MoveList& moves) const
{
	//can improve performance -> 
	//combine all fields in a bitboard and check for the non-sliding pieces
	//if the can take at these positions
	for (int castling_idx = 0; castling_idx < 2; castling_idx++)
	{
		CastlingType curr_castling_type = (CastlingType)castling_idx;

		if (_can_castle[_current_turn_color][curr_castling_type])
		{
			bool castling_allowed = true;
			for (int i = 0; i < 3; i++)
			{
				Square curr_square_to_check =
					SQUARES_FOR_KING_CASTLING[_current_turn_color][curr_castling_type][i];

				//square should not be attacked or should not have any piece there
				if (field_is_under_attack(curr_square_to_check) ||
					(i != 0 && (_board.all_pieces & BB_SQUARE[curr_square_to_check]) != 0ULL))
				{
					castling_allowed = false;
				}
			}
			//can be done better, but has to do for now
			if (curr_castling_type == castle_long)
			{
				//square that can be in check, but has to have no piece on it
				Square passingSquare = _current_turn_color == white ? B1 : B8;
				if ((_board.all_pieces & BB_SQUARE[passingSquare]) != 0ULL)
				{
					castling_allowed = false;
				}
			}

			if (castling_allowed)
			{
				moves.push_back(Move(_current_turn_color, curr_castling_type));
			}
		}
	}
}

void ChessBoard::get_en_passant_move(MoveList& moves) const
{
	if (_en_passant_square == SQUARE_NONE)
	{
		return;
	}

	Direction backwards = get_backward_for_color(_current_turn_color);

	Direction directions_where_own_pawn_could_be[2] =
	{ (Direction)(backwards + EAST), (Direction)(backwards + WEST) };

	for (int i = 0; i < 2; i++)
	{
		if (destination_is_on_board(_en_passant_square, directions_where_own_pawn_could_be[i]))
		{
			Square own_pawn_pos = (Square)(_en_passant_square + directions_where_own_pawn_could_be[i]);
			if ((BB_SQUARE[own_pawn_pos] &
				_board.pieces_of_color[_current_turn_color] &
				_board.pieces_of_type[pawn]) != 0ULL)
			{
				Square pawn_pos_to_delete = (Square)(_en_passant_square + backwards);
				moves.push_back(Move(own_pawn_pos, _en_passant_square));
			}
		}
	}
}

void ChessBoard::add_ray_moves(
	MoveList& moves,
	Square start,
	Direction directions[],
	int number_of_directions) const
{
	ChessColor opponent_color = get_opposite_color(_current_turn_color);

	for (int i = 0; i < number_of_directions; i++)
	{
		Direction current_direction = directions[i];

		Square current_square = start;
		while (true)
		{
			//if the new position is on the board
			if (destination_is_on_board(current_square, current_direction))
			{
				//set the new position
				current_square = (Square)(current_square + current_direction);

				//if the new position is the same color as the piece to check
				if (position_is_same_color(current_square, _current_turn_color))
				{
					//you cannot go on a square where a piece of the same color is
					break;
				}
				else if (position_is_same_color(current_square, opponent_color))
				{
					//if an opponent is on the new field you can take him,
					//but cannot continue after that (you cannot jump over opponents)
					moves.push_back(Move(start, current_square));
					break;
				}
				else {
					//if there is no piece at the new position you can move there.
					moves.push_back(Move(start, current_square));
				}
			}
			else {
				//if the new position is not on the board, the search should not continue
				break;
			}
		}
	}
}

bool ChessBoard::field_is_under_attack(Square pos, BitBoard moveBB) const
{
	//is only used for king checks and castling, so no en passant implemented

	ChessColor opponent_color = get_opposite_color(_current_turn_color);

	BitBoard new_current_color_bb = _board.pieces_of_color[_current_turn_color] ^ moveBB;

	BitBoard opponent_color_BB = (_board.pieces_of_color[opponent_color] & (~moveBB));

	BitBoard knight_BB = _board.pieces_of_type[knight];
	BitBoard pawns_BB = _board.pieces_of_type[pawn];
	BitBoard kings_BB = _board.pieces_of_type[king];

	//gets attacked by knight
	if ((KNIGHT_ATTACK_BB[pos] &
		opponent_color_BB &
		knight_BB) != 0ULL)
	{
		return true;
	}

	//gets attacked by pawn
	//it is handled like the current field is a pawn, 
	//because if the current field has a pawn on its attacking squares, 
	//it can also be attacked by the opponent pawn
	if ((PAWN_ATTACK_BB[_current_turn_color][pos] &
		opponent_color_BB &
		pawns_BB) != 0ULL)
	{
		return true;
	}

	//field gets attacked by king
	if ((KING_ATTACKS_BB[pos] &
		opponent_color_BB &
		kings_BB) != 0ULL)
	{
		return true;
	}

	//raycast in every direction and check for queen, rook or bishop attacks
	return field_gets_attacked_by_sliding_piece(pos, moveBB);
}

bool ChessBoard::field_gets_attacked_by_sliding_piece(Square pos, BitBoard moveBB) const
{
	ChessColor opponent_color = get_opposite_color(_current_turn_color);

	BitBoard queen_BB = _board.pieces_of_type[queen];
	BitBoard rook_BB = _board.pieces_of_type[rook];
	BitBoard bishop_BB = _board.pieces_of_type[bishop];

	BitBoard new_current_color_BB = _board.pieces_of_color[_current_turn_color] ^ moveBB;

	BitBoard moveBBWithoutStart = moveBB & ~_board.pieces_of_color[_current_turn_color];

	//if there are 2 destination fields, it is an en passant move
	if (((moveBBWithoutStart & _board.pieces_of_color[opponent_color]) != 0ULL) &&
		((moveBBWithoutStart & ~_board.pieces_of_color[opponent_color]) != 0ULL))
	{
		new_current_color_BB &= ~_board.pieces_of_color[opponent_color];
	}

	BitBoard opponent_color_BB = (_board.pieces_of_color[opponent_color] & (~moveBB));

	for (int i = 0; i < 8; i++)
	{
		Direction current_direction = ALL_SLIDING_DIRECTIONS[i];

		Square current_square = pos;
		while (true)
		{
			//if the new position would be on the board
			if (destination_is_on_board(current_square, current_direction))
			{
				//set the new position
				current_square = (Square)(current_square + current_direction);

				//if the new position is the same color as the piece to check
				if (square_overlaps_with_BB(current_square, new_current_color_BB))
				{
					//you cannot go on a square where a piece of the same color is
					break;
				}
				else if (square_overlaps_with_BB(current_square, opponent_color_BB))
				{
					BitBoard curr_pos_BB = BB_SQUARE[current_square];

					bool curr_dir_is_diagonal = i > 3;

					//found piece is a queen -> will attack no matter in which direction you are sliding
					if ((curr_pos_BB & queen_BB) != 0ULL)
					{
						//is queen
						return true;
					}
					//if found piece is a rook or a bishop, sliding direction matters
					else if (curr_dir_is_diagonal)
					{
						if ((curr_pos_BB & bishop_BB) != 0ULL)
						{
							//is bishop
							return true;
						}
					}
					else
					{
						if ((curr_pos_BB & rook_BB) != 0ULL)
						{
							//is rook
							return true;
						}
					}
					//if the found piece is an enemy, but no sliding piece then it does not attack you
					break;
				}
			}
			else
			{
				//if the new position is not on the board, the search should not continue
				break;
			}
		}
	}
	return false;
}

bool ChessBoard::move_is_legal(const Move move) const
{
	//if move is castle -> return true
	if (move.get_flag() == castle)
	{
		//because a castling move has been checked to be legal before
		return true;
	}

	Square start = move.get_start();
	Square dest = move.get_destination();

	//TODO
	return true;
	/*BitBoard BBforNextMove = move.getBBWithMoveDone();

	Square king_pos = _board.king_pos[_current_turn_color];

	return start == king_pos ?
		!field_is_under_attack(dest, BBforNextMove) :
		!field_is_under_attack(king_pos, BBforNextMove);*/
}

bool ChessBoard::is_capture_move(const Move move) const
{
	MoveFlag flag = move.get_flag();
	if (flag == castle)
	{
		return false;
	}
	else if(flag == en_passant)
	{
		return true;
	}

	BitBoard opposite_color_BB = _board.pieces_of_color[get_opposite_color(_current_turn_color)];
	BitBoard potential_capture_field = BB_SQUARE[move.get_destination()];

	return bitboards_overlap(opposite_color_BB, potential_capture_field);
}

void ChessBoard::update_castling_rights_after_move(const Move& m)
{
	BitBoard start = BB_SQUARE[m.get_start()];
	BitBoard dest = BB_SQUARE[m.get_destination()];
	if (bitboards_overlap(start, SQUARES_EFFECTED_BY_CASTLING_BB) ||
		bitboards_overlap(dest, SQUARES_EFFECTED_BY_CASTLING_BB))
	{

		if ((KINGFILE & BACKRANK[_current_turn_color] & start) != 0)
		{
			_can_castle[_current_turn_color][castle_long] = false;
			_can_castle[_current_turn_color][castle_short] = false;
		}

		for (int i = 0; i < 2; i++)
		{
			ChessColor curr_col = (ChessColor)i;
			for (int j = 0; j < 2; j++)
			{
				CastlingType curr_castle_type = (CastlingType)j;
				BitBoard field_to_check = BACKRANK[curr_col] & CASTLINGSIDE[curr_castle_type];
				if (bitboards_overlap(start, field_to_check) ||
					bitboards_overlap(dest, field_to_check))
				{
					_can_castle[curr_col][curr_castle_type] = false;
				}
			}
		}
	}
}

void ChessBoard::update_en_passant_rights_after_move(const Move& m)
{
	_en_passant_square = SQUARE_NONE;
	Square start = m.get_start();
	if (square_overlaps_with_BB(start, _board.pieces_of_type[pawn]))
	{
		Square dest = m.get_destination();
		BitBoard start_rank_for_double_move = _current_turn_color == white ? RANK_2 : RANK_7;
		BitBoard dest_rank_for_double_move = _current_turn_color == white ? RANK_4 : RANK_5;

		if (square_overlaps_with_BB(start, start_rank_for_double_move) &&
			square_overlaps_with_BB(dest, dest_rank_for_double_move))
		{
			_en_passant_square = (Square)(start + get_forward_for_color(_current_turn_color));
		}
	}
}

void ChessBoard::update_50_move_rule(const Move& m)
{
	BitBoard start_BB = BB_SQUARE[m.get_start()];
	BitBoard dest_BB = BB_SQUARE[m.get_destination()];
	ChessColor opponent_color = get_opposite_color(_current_turn_color);

	if (bitboards_overlap(start_BB, _board.pieces_of_type[pawn]) ||
		bitboards_overlap(dest_BB, _board.pieces_of_color[opponent_color]))
	{
		_half_move_clock = 0;
	}
	else
	{
		_half_move_clock++;
	}
}

bool ChessBoard::insufficient_material_check() const
{
	//if any of these pieces are on the board, the game can be won
	if (_board.pieces_of_type[queen] != 0 ||
		_board.pieces_of_type[rook] != 0 ||
		_board.pieces_of_type[pawn] != 0)
	{
		return false;
	}

	if (_board.pieces_of_type[bishop] == 0 &&
		_board.pieces_of_type[knight] == 0)
	{
		return true;
	}

	//TODO
	//if only one bishop or one knight is on the board, the game cant be won

	return false;
}

char ChessBoard::get_piece_at(Square pos) const
{
	BitBoard pos_BB = BB_SQUARE[pos];

	if (bitboards_overlap(pos_BB, ~_board.all_pieces))
	{
		return ' ';
	}

	char piece_char = '~';

	for (int i = 0; i < NUMBER_OF_DIFFERENT_PIECE_TYPES; i++)
	{
		PieceType curr_type = (PieceType)i;

		if (bitboards_overlap(_board.pieces_of_type[curr_type], pos_BB))
		{
			piece_char = PIECETYPE_CHAR[curr_type];
		}
	}

	if (piece_char == '~')
	{
		throw "Could not find PieceType in the Chessboard configuration";
	}

	if (bitboards_overlap(_board.pieces_of_color[black], pos_BB))
	{
		piece_char = char_to_lower(piece_char);
	}

	return piece_char;
}


ChessBoard::ChessBoard(std::string given_fen_code)
{
	//set all castling rights to false at the beginning
	for (int i = 0; i < 2; i++)
	{
		ChessColor curr_color = (ChessColor)i;
		for (int j = 0; j < 2; j++)
		{
			CastlingType curr_castle_type = (CastlingType)j;
			_can_castle[curr_color][curr_castle_type] = false;
		}
	}

	std::string prefix_for_errors = "ERROR The given FEN Code is invalid. ";

	std::vector<std::string> split_fen_code = split_string(given_fen_code, ' ');
	if (split_fen_code.size() != 6)
	{
		throw prefix_for_errors + "It had not the right size";
	}

	//the implementation of the iteration will be a bit weird,
	//since index 0 is a1 and in the fen code it is a8

	int curr_rank_start_idx = 56;
	int curr_file = 0;

	//fill the board
	for (int curr_str_idx = 0;
		curr_str_idx < split_fen_code[0].size();
		curr_str_idx++)
	{
		char curr_char = given_fen_code[curr_str_idx];

		int board_pos = curr_rank_start_idx + curr_file;

		if (curr_char <= '8' && curr_char >= '1')
		{
			int fields_to_skip = curr_char - '0';
			curr_file += fields_to_skip;
		}
		else if (curr_char == '/')
		{
			curr_rank_start_idx -= 8;
			curr_file = -1;
			curr_file++;
		}
		else
		{
			ChessPiece piece(curr_char);

			_board.set_at_position(piece, (Square)board_pos);

			curr_file++;
		}
	}

	//get the turn color
	if (split_fen_code[1].size() != 1)
	{
		throw prefix_for_errors + "The turn color should only occupy 1 char";
	}
	_current_turn_color =
		split_fen_code[1][0] == 'w' ? white :
		split_fen_code[1][0] == 'b' ? black :
		throw prefix_for_errors + "The color could not be found";

	//castling rights
	for (int i = 0; i < split_fen_code[2].size(); i++)
	{
		char curr_char = split_fen_code[2][i];

		if (curr_char != '-')
		{
			_can_castle
				[get_color_of_fen_char(curr_char)]
			[get_castling_type_of_fen_char(curr_char)] = true;
		}
	}

	//en passant field
	_en_passant_square = get_square_from_string(split_fen_code[3]);

	//50 move rule - after half moves without pushing a pawn and
	//without capturing a piece the game ends in a draw
	_half_move_clock = std::stoi(split_fen_code[4]);

	//keeps track of the moves (one move consists of one move of white and one move of black)
	_move_number = std::stoi(split_fen_code[5]);
}

std::string ChessBoard::get_string()
{
	std::string result = "";
	std::string row_seperator_string = "\n+---+---+---+---+---+---+---+---+\n";
	result += row_seperator_string;

	for (int rank = 7; rank >= 0; rank--)
	{
		for (int file = 0; file < 8; file++)
		{
			Square pos = (Square)(rank * 8 + file);
			result += "| ";
			result += get_piece_at(pos);
			result += " ";

		}
		result += "|" + std::to_string(rank + 1);
		result += row_seperator_string;
	}
	result += "  a   b   c   d   e   f   g   h\n";

	return result;
}

std::string ChessBoard::get_fen()
{
	std::string result = "";

	//written with copilot. can be improved i think

	for (int rank = 7; rank >= 0; rank--)
	{
		int empty_fields = 0;
		for (int file = 0; file < 8; file++)
		{
			Square pos = (Square)(rank * 8 + file);
			char piece_char = get_piece_at(pos);

			if (piece_char == ' ')
			{
				empty_fields++;
			}
			else
			{
				if (empty_fields > 0)
				{
					result += std::to_string(empty_fields);
					empty_fields = 0;
				}
				result += piece_char;
			}
		}
		if (empty_fields > 0)
		{
			result += std::to_string(empty_fields);
		}
		if (rank > 0)
		{
			result += "/";
		}
	}

	result += " ";

	result += _current_turn_color == white ? "w" : "b";

	result += " ";

	if (_can_castle[white][castle_short] ||
		_can_castle[white][castle_long] ||
		_can_castle[black][castle_short] ||
		_can_castle[black][castle_long])
	{
		if (_can_castle[white][castle_short])
		{
			result += "K";
		}
		if (_can_castle[white][castle_long])
		{
			result += "Q";
		}
		if (_can_castle[black][castle_short])
		{
			result += "k";
		}
		if (_can_castle[black][castle_long])
		{
			result += "q";
		}
	}
	else
	{
		result += "-";
	}

	result += " ";

	result += SQUARE_STRING[_en_passant_square];

	result += " ";

	result += std::to_string(_half_move_clock);

	result += " ";

	result += std::to_string(_move_number);

	return result;
}

ChessColor ChessBoard::get_current_turn_color() const
{
	return _current_turn_color;
}

int ChessBoard::get_number_of_moves_played() const
{
	return _move_number;
}

bool ChessBoard::is_king_in_check() const
{
	return field_is_under_attack(_board.king_pos[_current_turn_color]);
}

MoveList ChessBoard::get_all_legal_moves() const
{
	MoveList move_list;

	BitBoard attack_bb = BITBOARD_NONE;
	
	//get all squares that are under attack
	Square king_pos = _board.king_pos[_current_turn_color];
	
	
	

	get_pawn_moves(move_list);
	get_knight_moves(move_list);
	get_bishop_moves(move_list);
	get_rook_moves(move_list);
	get_queen_moves(move_list);
	get_king_moves(move_list);

	get_castling_moves(move_list);
	get_en_passant_move(move_list);

	return move_list;
}

MoveList ChessBoard::get_all_legal_capture_moves() const
{
	MoveList list = get_all_legal_moves();

	list.erase
	(
		std::remove_if
		(
			list.begin(),
			list.end(),
			[this](const Move move)
			{
				return !is_capture_move(move);
			}
		),
		list.end()
				);

	return list;
}

void ChessBoard::make_move(const Move& move)
{
	Square move_start = move.get_start();
	Square move_dest = move.get_destination();

	update_castling_rights_after_move(move);
	update_en_passant_rights_after_move(move);
	update_50_move_rule(move);

	move.execute(_board);

	if (move_start == _board.king_pos[_current_turn_color])
	{
		_board.king_pos[_current_turn_color] = move_dest;
	}

	if (_current_turn_color == black)
	{
		_move_number++;
	}

	_current_turn_color = get_opposite_color(_current_turn_color);
}

ChessBoard ChessBoard::get_copy_by_value() const
{
	ChessBoard board(EMPTY_FEN);
	board._board = _board;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			board._can_castle[i][j] = _can_castle[i][j];
		}
	}

	board._current_turn_color = _current_turn_color;

	board._en_passant_square = _en_passant_square;

	board._half_move_clock = _half_move_clock;

	board._move_number = _move_number;

	return board;
}

GameState ChessBoard::get_game_state() const
{
	if (get_all_legal_moves().size() == 0)
	{
		if (field_is_under_attack(_board.king_pos[_current_turn_color]))
		{
			return _current_turn_color == white ? black_won : white_won;
		}
		else
		{
			return stalemate;
		}
	}
	if (_half_move_clock == 50 ||
		insufficient_material_check())
	{
		return draw;
	}
	return ongoing;
}

GameDurationState ChessBoard::get_game_duration_state() const
{
	//HAS TO BE IMPROVED ALOT
	// 
	// 
	//description at the end of: https://www.chessprogramming.org/Simplified_Evaluation_Function

	//definiton on the site of when the endgame begins:
	//- Both sides have no queens or
	//- Every side which has a queen has additionally no other pieces or one minorpiece maximum.

	//there are different game states for different colors
	//for example: if one color got lots of pieces, but the other almost none, 
	//it is useful to bring the king into the game
	ChessColor col = _current_turn_color;
	BitBoard colorBB = _board.pieces_of_color[col];

	if (((_board.pieces_of_type[queen] == 0ULL) &&
		//a queen can be exchanged very early on. So we need to check if the game has already progressed a bit
		_move_number > 10))
	{
		//gets activated often at the start of games, 
		//which is not exactly an "endgame" state
		//return EndGame;
	}


	if ((_board.pieces_of_type[queen] & colorBB) != 0ULL)
	{
		BitBoard colorBBWithoutKingOrQueen =
			colorBB &
			~_board.pieces_of_type[king] &
			~_board.pieces_of_type[queen];

		if ((colorBBWithoutKingOrQueen & ~_board.pieces_of_type[bishop]) == 0ULL ||
			(colorBBWithoutKingOrQueen & ~_board.pieces_of_type[knight]) == 0ULL ||
			(colorBBWithoutKingOrQueen & ~_board.pieces_of_type[pawn]) == 0ULL ||
			(colorBBWithoutKingOrQueen & ~_board.pieces_of_type[rook]) == 0ULL)
		{
			return EndGame;
		}
	}


	return MidGame;
}

BoardRepresentation ChessBoard::get_board_representation() const
{
	return _board;
}

bool operator==(const ChessBoard& first, const ChessBoard& second)
{
	bool retVal = first._board == second._board;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			retVal = retVal && (first._can_castle[i][j] == second._can_castle[i][j]);
		}
	}

	retVal = retVal && (first._current_turn_color == second._current_turn_color);

	retVal = retVal && (first._en_passant_square == second._en_passant_square);

	retVal = retVal && (first._half_move_clock == second._half_move_clock);

	retVal = retVal && (first._move_number == second._move_number);

	return retVal;
}

bool operator!=(const ChessBoard& first, const ChessBoard& second)
{
	return !(first == second);
}