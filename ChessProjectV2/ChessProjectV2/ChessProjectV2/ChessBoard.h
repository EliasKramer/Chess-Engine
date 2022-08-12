#pragma once
#include "BitBoard.h"
#include "DataAndTypes.h"
#include <string>
#include "ChessPiece.h"
#include "HelpMethods.h"

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
	Square _lastEnPassantMove;

	//keeps track of the 50 moves rule
	uint16_t _halfMovesSincePawnOrCaptureMove;

	//the move number. 
	//increases every time when black makes a move
	uint16_t _moveNumber;
public:
	ChessBoard();
	ChessBoard(std::string given_fen_code);
	void setupBoard();
};