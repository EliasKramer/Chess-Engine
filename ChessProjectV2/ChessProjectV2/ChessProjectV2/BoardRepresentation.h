#pragma once
#include "BitBoard.h"
#include "DataAndTypes.h"
#include "Constants.h"
#include "ChessPiece.h"
#include <vector>

class BoardRepresentation
{
public:
	BitBoard all_pieces;
	BitBoard pieces_of_color[DIFFERENT_CHESS_COLORS];
	BitBoard pieces_of_type[NUMBER_OF_DIFFERENT_PIECE_TYPES];

	Square king_pos[DIFFERENT_CHESS_COLORS];

	//a list of all piece positions. first index is color, second is piece type
	std::vector<Square> piece_positions[DIFFERENT_CHESS_COLORS][NUMBER_OF_DIFFERENT_PIECE_TYPES];

	BoardRepresentation();

	ChessPiece get_piece_at(Square square) const;

	void set_at_position(ChessPiece piece, Square position);

	void del_at_pos(Square position);

	void move_from_pos_to_pos(Square start, Square destination);

private:
	//be aware, that this does not overwrite the Bitboard, it only adds it
	void set_piece_bitboard(ChessPiece piece, BitBoard bitboard);

	void remove_from_piece_list(ChessPiece piece, Square position);
	void remove_all_from_piece_list_at(Square position);
};
bool operator==(const BoardRepresentation& first, const BoardRepresentation& second);
bool operator!=(const BoardRepresentation& first, const BoardRepresentation& second);