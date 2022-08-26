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

	bool destinationIsOnBoard(Square start, Direction direction);
	bool destinationIsSameColor(Square start, Direction direction, ChessColor color);
	bool positionIsSameColor(Square pos, ChessColor color);

	void addIfDestinationIsValid(
		MoveList& moves,
		Square start,
		Direction dir,
		PieceType type);
	void addIfDestinationIsColor(
		MoveList& moves,
		Square start,
		Direction dir,
		ChessColor color,
		PieceType type);

	//Pseudo legal moves are moves that follow 
	//the move rules for the types.
	//They do not check if the king is in check
	MoveList getAllPseudoLegalMoves();

	void getPawnMoves(MoveList& moves);
	void getKnightMoves(MoveList& moves);
	void getBishopMoves(MoveList& moves);
	void getRookMoves(MoveList& moves);
	void getQueenMoves(MoveList& moves);
	void getKingMoves(MoveList& moves);

	void getCastlingMoves(MoveList& moves);
	void getEnPassantMove(MoveList& moves);

	void addRayMoves(
		MoveList& moves,
		Square start,
		PieceType type,
		Direction directions[],
		int numberOfDirections);

public:
	ChessBoard();
	ChessBoard(std::string given_fen_code);

	//returns all moves of the color, whos turn it is
	MoveList getAllLegalMoves();
};