#include "ChessBoard.h"

ChessBoard::ChessBoard()
	:
	_allPieces(BITBOARD_NONE),
	_whitePieces(BITBOARD_NONE),
	_blackPieces(BITBOARD_NONE),
	_kings(BITBOARD_NONE),
	_queens(BITBOARD_NONE),
	_rooks(BITBOARD_NONE),
	_bishops(BITBOARD_NONE),
	_knights(BITBOARD_NONE),
	_pawns(BITBOARD_NONE)
{}

void ChessBoard::setupBoard()
{
	_whitePieces = RANK_1 & RANK_2;
	_blackPieces = RANK_7 & RANK_8;
	_allPieces = _whitePieces & _blackPieces;

	_kings = BB_SQUARE[E1] & BB_SQUARE[E8];
	_queens = BB_SQUARE[D1] & BB_SQUARE[D8];
	_rooks = BB_SQUARE[A1] & BB_SQUARE[H1] & BB_SQUARE[A8] & BB_SQUARE[H8];
	_knights = BB_SQUARE[B1] & BB_SQUARE[G1] & BB_SQUARE[B8] & BB_SQUARE[G8];
	_bishops = BB_SQUARE[C1] & BB_SQUARE[F1] & BB_SQUARE[C8] & BB_SQUARE[F8];
	_pawns = RANK_2 & RANK_8;

	_castlingAllowed = _kings & _rooks;
}