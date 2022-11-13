#pragma once
#include "BitBoard.h"
#include "DataAndTypes.h"
#include <string>
#include "ChessPiece.h"
#include "HelpMethods.h"
#include "Move.h"
#include "Constants.h"
#include "BoardRepresentation.h"

const std::string STARTING_FEN =
"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

const std::string EMPTY_FEN =
"8/8/8/8/8/8/8/8 w - - 0 1";

class ChessBoard
{
protected:
	BoardRepresentation _board;

	//the first dimension is color and 
	//the second is the type. 
	//aka long or short castling
	bool _can_castle[2][2];

	//the players color, whose turn it is
	ChessColor _current_turn_color;

	//if an en passant move is possible, 
	//the square, where the opponent has to go to
	//will be stored here
	Square _en_passant_square;

	//keeps track of the 50 moves rule
	uint16_t _half_move_clock;

	//the move number. 
	//increases every time when black makes a move
	uint16_t _move_number;

	/*Move Generation*/
	bool destination_is_same_color(Square start, Direction direction, ChessColor color) const;
	bool position_is_same_color(Square pos, ChessColor color) const;
	
	void add_if_destination_is_valid(
		MoveList& moves,
		Square start,
		Direction dir) const;
	void add_if_destination_is_color(
		MoveList& moves,
		Square start,
		Direction dir,
		ChessColor color) const;

	void get_pawn_moves(MoveList& moves) const;
	void get_knight_moves(MoveList& moves) const;
	void get_bishop_moves(MoveList& moves) const;
	void get_rook_moves(MoveList& moves) const;
	void get_queen_moves(MoveList& moves) const;
	void get_king_moves(MoveList& moves) const;

	void add_pawn_move(
		MoveList& moves, Square start, Square dest) const;
	void get_castling_moves(MoveList& moves) const;
	void get_en_passant_move(MoveList& moves) const;
	
	void add_ray_moves(
		MoveList& moves,
		Square start,
		Direction directions[],
		int numberOfDirections) const;

	//square gets attacke by the opponent
	bool field_is_under_attack(Square pos, BitBoard moveBB = BITBOARD_NONE) const;
	//checks if square gets attacked by sliding pieces
	bool field_gets_attacked_by_sliding_piece(Square pos, BitBoard moveBB = BITBOARD_NONE) const;

	bool move_is_legal(const Move move) const;
	bool is_capture_move(const Move move) const;
	
	void update_castling_rights_after_move(const Move& m);
	
	void update_en_passant_rights_after_move(const Move& m);

	void update_50_move_rule(const Move& m);

	//checks if any side has enough material/pieces to win the game
	bool insufficient_material_check() const;
	
	char get_piece_at(Square pos) const;

	friend bool operator ==(const ChessBoard& first, const ChessBoard& second);
	friend bool operator !=(const ChessBoard& first, const ChessBoard& second);
public:
	ChessBoard(std::string given_fen_code = STARTING_FEN);
	
	std::string get_string();
	std::string get_fen();

	ChessColor get_current_turn_color() const;
	int get_number_of_moves_played() const;
	
	//returns true if the king is in check
	bool is_king_in_check() const;

	//returns all moves of the color, whos turn it is
	MoveList get_all_legal_moves() const;
	MoveList get_all_legal_capture_moves() const;

	//execute move
	void make_move(const Move& move);

	//copy board by value
	ChessBoard get_copy_by_value() const;

	GameState get_game_state() const;
	GameDurationState get_game_duration_state() const;

	BoardRepresentation get_board_representation() const;
};

bool operator ==(const ChessBoard& first, const ChessBoard& second);
bool operator !=(const ChessBoard& first, const ChessBoard& second);