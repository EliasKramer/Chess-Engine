#include "BoardRepresentation.h"

BoardRepresentation::BoardRepresentation()
	:
	all_pieces(BITBOARD_NONE),
	pieces_of_color{
	BITBOARD_NONE,
	BITBOARD_NONE },

	pieces_of_type{
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE },
	
	king_pos{E1, E8}
{}

ChessPiece BoardRepresentation::get_piece_at(Square square) const
{
	BitBoard square_BB = BB_SQUARE[square];
	//can be improved by adding null types
	ChessColor col_found = no_color;
	PieceType type_found = no_type;

	for (int i = 0; i < DIFFERENT_CHESS_COLORS; i++)
	{
		ChessColor curr_col = (ChessColor)i;

		if (bitboards_overlap(pieces_of_color[curr_col], square_BB))
		{
			col_found = curr_col;
			break;
		}
	}
	for (int i = 0; i < NUMBER_OF_DIFFERENT_PIECE_TYPES; i++)
	{
		PieceType curr_type = (PieceType)i;

		if (bitboards_overlap(pieces_of_type[curr_type], square_BB))
		{
			type_found = curr_type;
			break;
		}
	}

	return ChessPiece(col_found, type_found);
}

void BoardRepresentation::set_at_position(ChessPiece piece, Square position)
{
	if(piece.get_type() == king)
	{
		king_pos[piece.get_color()] = position;
	}

	piece_positions[piece.get_color()][piece.get_type()].push_back(position);

	set_piece_bitboard(piece, BB_SQUARE[position]);
}

void BoardRepresentation::del_at_pos(Square position)
{
	BitBoard keep_piece_mask = ~(BB_SQUARE[position]);

	all_pieces = all_pieces & keep_piece_mask;

	for (int i = 0; i < DIFFERENT_CHESS_COLORS; i++)
	{
		ChessColor curr_col = (ChessColor)i;
		pieces_of_color[curr_col] = pieces_of_color[curr_col] & keep_piece_mask;
	}

	for (int i = 0; i < NUMBER_OF_DIFFERENT_PIECE_TYPES; i++)
	{
		PieceType curr_type = (PieceType)i;
		pieces_of_type[curr_type] = pieces_of_type[curr_type] & keep_piece_mask;
	}

	remove_all_from_piece_list_at(position);
}

void BoardRepresentation::move_from_pos_to_pos(Square start, Square destination)
{
	BitBoard start_pos_BB = BB_SQUARE[start];
	BitBoard dest_pos_BB = BB_SQUARE[destination];

	ChessPiece start_piece = get_piece_at(start);
	ChessPiece dest_piece = get_piece_at(destination);

	//if there is not piece to move return
	if (!start_piece.is_valid())
	{
		return;
	}
	if (dest_piece.is_valid())
	{
		del_at_pos(destination);
	}

	//add piece to the color bitboard
	pieces_of_color[start_piece.get_color()] = pieces_of_color[start_piece.get_color()] | dest_pos_BB;
	//add piece to the type bitboard
	pieces_of_type[start_piece.get_type()] = pieces_of_type[start_piece.get_type()] | dest_pos_BB;
	//add piece to the all bitbaord
	all_pieces = all_pieces | dest_pos_BB;

	del_at_pos(start);
}

void BoardRepresentation::set_piece_bitboard(ChessPiece piece, BitBoard bitboard)
{
	all_pieces = all_pieces | bitboard;

	ChessColor col = piece.get_color();
	pieces_of_color[col] = pieces_of_color[col] | bitboard;

	PieceType type = piece.get_type();
	pieces_of_type[type] = pieces_of_type[type] | bitboard;
}

void BoardRepresentation::remove_from_piece_list(ChessPiece piece, Square position)
{
	std::vector<Square>& piece_list = piece_positions[piece.get_color()][piece.get_type()];

	for (int i = 0; i < piece_list.size(); i++)
	{
		if (piece_list[i] == position)
		{
			piece_list.erase(piece_list.begin() + i);
			break;
		}
	}
}

void BoardRepresentation::remove_all_from_piece_list_at(Square position)
{
	for (int i = 0; i < DIFFERENT_CHESS_COLORS; i++)
	{
		ChessColor curr_col = (ChessColor)i;
		
		for (int j = 0; j < NUMBER_OF_DIFFERENT_PIECE_TYPES; j++)
		{
			PieceType curr_type = (PieceType)j;

			remove_from_piece_list(ChessPiece(curr_col, curr_type), position);
		}
	}
}

//Equals Operator

bool operator==(const BoardRepresentation& first, const BoardRepresentation& second)
{
	bool ret_val = first.all_pieces == second.all_pieces
		&& (first.pieces_of_color[white] == second.pieces_of_color[white])
		&& (first.pieces_of_color[black] == second.pieces_of_color[black]);

	for (int i = 0; i < NUMBER_OF_DIFFERENT_PIECE_TYPES; i++)
	{
		ret_val = ret_val && (first.pieces_of_type[i] == second.pieces_of_type[i]);
	}

	ret_val = ret_val && (first.king_pos[white] == second.king_pos[white]);
	ret_val = ret_val && (first.king_pos[black] == second.king_pos[black]);

	return ret_val;
}

bool operator!=(const BoardRepresentation& first, const BoardRepresentation& second)
{
    return !(first == second);
}