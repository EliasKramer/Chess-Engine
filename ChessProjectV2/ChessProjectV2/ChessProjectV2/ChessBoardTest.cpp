#include "ChessBoardTest.h"

ChessBoardTest::ChessBoardTest(std::string given_fen_code)
	:ChessBoard(given_fen_code)
{}

BitBoard ChessBoardTest::get_all_pieces()
{
	return _board.all_pieces;
}

BitBoard ChessBoardTest::get_all_pieces_of_color(ChessColor color)
{
	return _board.pieces_of_color[color];
}

BitBoard ChessBoardTest::get_all_pieces_of_type(PieceType type)
{
	return _board.pieces_of_type[type];
}

bool ChessBoardTest::move_is_legal(const Move move)
{
	return ChessBoard::move_is_legal(move);
}

bool ChessBoardTest::is_castling_allowed(ChessColor color, CastlingType option)
{
	return _can_castle[color][option];
}

ChessColor ChessBoardTest::get_turn_color()
{
	return _current_turn_color;
}

Square ChessBoardTest::get_en_passant_square()
{
	return _en_passant_square;
}

uint16_t ChessBoardTest::get_half_move_clock()
{
	return _half_move_clock;
}

bool ChessBoardTest::field_is_under_attack(Square pos)
{
	return ChessBoard::field_is_under_attack(pos);
}

uint16_t ChessBoardTest::get_move_number()
{
	return _move_number;
}