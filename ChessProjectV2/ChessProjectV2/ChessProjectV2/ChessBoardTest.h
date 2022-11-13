#pragma once
#include "ChessBoard.h"
#include "DataAndTypes.h"
#include <string>

//this is a test class. it is only there to read variables, that are ususally hidden
//from the user
class ChessBoardTest : public ChessBoard
{
public:
	//constructors
	
	ChessBoardTest(std::string given_fen_code);
	
	//getter for the base class

	BitBoard get_all_pieces();

	bool field_is_under_attack(Square pos);

	BitBoard get_all_pieces_of_color(ChessColor color);
	BitBoard get_all_pieces_of_type(PieceType type);
	bool is_castling_allowed(ChessColor color, CastlingType option);
	ChessColor get_turn_color();
	Square get_en_passant_square();
	uint16_t get_half_move_clock();
	uint16_t get_move_number();
	
	bool move_is_legal(const Move move);
};