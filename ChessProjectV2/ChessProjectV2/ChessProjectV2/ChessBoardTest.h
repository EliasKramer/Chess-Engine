#pragma once
#include "ChessBoard.h"
#include "DataAndTypes.h"
#include <string>
class ChessBoardTest : public ChessBoard
{
public:
	//constructors
	
	ChessBoardTest();
	ChessBoardTest(std::string given_fen_code);
	
	//setup board directly
	void setupBoard();
	//getter for the base class

	BitBoard getAllPieces();
	BitBoard getAllPiecesOfColor(ChessColor color);
	BitBoard getAllPiecesOfType(PieceType type);
	bool casltingAllowed(ChessColor color, CastlingType option);
	ChessColor getTurnColor();
	Square getEnPassantSquare();
	uint16_t getHalfMoveClock();
	uint16_t getMoveNumber();

	UniqueMoveList getPseudoLegalMoves();
};