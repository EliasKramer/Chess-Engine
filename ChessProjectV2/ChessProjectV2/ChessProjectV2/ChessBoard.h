#pragma once
#include "BitBoard.h"
#include "DataAndTypes.h"
#include <string>
#include "ChessPiece.h"
#include "HelpMethods.h"
#include "Move.h"

const std::string STARTING_FEN =
"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

class ChessBoard
{
protected:
	BitBoard _allPieces;
	BitBoard _piecesOfColor[DIFFERENT_CHESS_COLORS];
	BitBoard _piecesOfType[NUMBER_OF_DIFFERENT_PIECE_TYPES];

	//the first dimension is color and 
	//the second is the type. 
	//aka long or short castling
	bool _canCastle[2][2];

	//the players color, whose turn it is
	ChessColor _currentTurnColor;

	//if an en passant move is possible, 
	//the square, where the opponent has to go to
	//will be stored here
	Square _enPassantSquare;

	//keeps track of the 50 moves rule
	uint16_t _halfMoveClock;

	//the move number. 
	//increases every time when black makes a move
	uint16_t _moveNumber;

	/*Move Generation*/
	
	bool positionIsValid(Square start, Direction dirToAdd);

	//Pseudo legal moves are moves that follow 
	//the move rules for the types.
	//They do not check if the king is in check
	UniqueMoveList getAllPseudoLegalMoves();

	PieceType getTypeAtSquare(Square square);

	void getMovesOfType(UniqueMoveList& moves, Square square);

	void getPawnMoves(UniqueMoveList& moves, Square square);
	void getKnightMoves(UniqueMoveList& moves, Square square);
	void getBishopMoves(UniqueMoveList& moves, Square square);
	void getRookMoves(UniqueMoveList& moves, Square square);
	void getQueenMoves(UniqueMoveList& moves, Square square);
	void getKingMoves(UniqueMoveList& moves, Square square);

	void getCastlingMoves(UniqueMoveList& moves);
	void getEnPassantMove(UniqueMoveList& moves);

public:
	ChessBoard();
	ChessBoard(std::string given_fen_code);

	//returns all moves of the color, whos turn it is
	UniqueMoveList getAllLegalMoves();
};