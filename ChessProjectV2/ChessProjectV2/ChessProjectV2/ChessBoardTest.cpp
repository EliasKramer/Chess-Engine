#include "ChessBoardTest.h"

void ChessBoardTest::setupBoard()
{
	_piecesOfColor[White] = RANK_1 | RANK_2;
	_piecesOfColor[Black] = RANK_7 | RANK_8;
	_allPieces =
		_piecesOfColor[White] |
		_piecesOfColor[Black];

	_piecesOfType[King] = BB_SQUARE[E1] | BB_SQUARE[E8];
	_piecesOfType[Queen] = BB_SQUARE[D1] | BB_SQUARE[D8];
	_piecesOfType[Rook] = BB_SQUARE[A1] | BB_SQUARE[H1] | BB_SQUARE[A8] | BB_SQUARE[H8];
	_piecesOfType[Knight] = BB_SQUARE[B1] | BB_SQUARE[G1] | BB_SQUARE[B8] | BB_SQUARE[G8];
	_piecesOfType[Bishop] = BB_SQUARE[C1] | BB_SQUARE[F1] | BB_SQUARE[C8] | BB_SQUARE[F8];
	_piecesOfType[Pawn] = RANK_2 | RANK_7;

	for (int colorIdx = 0; colorIdx < DIFFERENT_CHESS_COLORS; colorIdx++)
	{
		for (int typeIdx = 0; typeIdx < DIFFERENT_CASTLING_TYPES; typeIdx++)
		{
			//white black long and short castling enabled at the start
			_canCastle[colorIdx][typeIdx] = true;
		}
	}

	_currentTurnColor = White;

	_enPassantSquare = SQUARE_NONE;

	_halfMoveClock = 0;

	_moveNumber = 1;
}
ChessBoardTest::ChessBoardTest()
    :ChessBoard()
{}

ChessBoardTest::ChessBoardTest(std::string given_fen_code)
    :ChessBoard(given_fen_code)
{}

BitBoard ChessBoardTest::getAllPieces()
{
    return _allPieces;
}

BitBoard ChessBoardTest::getAllPiecesOfColor(ChessColor color)
{
    return _piecesOfColor[color];
}

BitBoard ChessBoardTest::getAllPiecesOfType(PieceType type)
{
    return _piecesOfType[type];
}

MoveList ChessBoardTest::getPseudoLegalMoves()
{
	return ChessBoard::getAllPseudoLegalMoves();
}

bool ChessBoardTest::destinationIsOnBoard(Square start, Direction dirToAdd)
{
	return ChessBoard::destinationIsOnBoard(start, dirToAdd);
}

bool ChessBoardTest::casltingAllowed(ChessColor color, CastlingType option)
{
	return _canCastle[color][option];
}

ChessColor ChessBoardTest::getTurnColor()
{
    return _currentTurnColor;
}

Square ChessBoardTest::getEnPassantSquare()
{
    return _enPassantSquare;
}

uint16_t ChessBoardTest::getHalfMoveClock()
{
    return _halfMoveClock;
}

uint16_t ChessBoardTest::getMoveNumber()
{
    return _moveNumber;
}