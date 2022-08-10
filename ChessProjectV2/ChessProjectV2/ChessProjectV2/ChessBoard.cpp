#include "ChessBoard.h"

ChessBoard::ChessBoard()
	:
	_allPieces(BITBOARD_NONE),
	_piecesOfColor{
	BITBOARD_NONE,
	BITBOARD_NONE},
	
	_piecesOfType{ 
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE}
{
	
}

ChessBoard::ChessBoard(std::string given_fen_code)
{
	//the implementation of the iteration will be a bit weird,
	//since index 0 is a1 and in the fen code it is a8
	
	//start fen is: 
	//rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

	int currStringIdx = 0;
	int currRankStartIdx = 56;
	int currFile = 0;

	//fill the board
	while (given_fen_code[currStringIdx] != ' ')
	{
		char currChar = given_fen_code[currStringIdx];
		
		int boardPos = currRankStartIdx + currFile;
		
		//number
		if (currChar <= '8' && currChar >= '1')
		{
			int fieldsToSkip = currChar - '0';
			currFile += fieldsToSkip;
		}
		else if (currChar == '/')
		{
			currRankStartIdx -= 8;
			currFile = -1;
		}
		else {
			BitBoard bbToAdd = BB_SQUARE[boardPos];
			_allPieces |= bbToAdd;
			
			//place
		}
		currFile++;
		
		currStringIdx++;
	}

	//implement turn and castling
}

void ChessBoard::setupBoard()
{
	_piecesOfColor[White] = RANK_1 & RANK_2;
	_piecesOfColor[Black] = RANK_7 & RANK_8;
	_allPieces = 
		_piecesOfColor[White] &
		_piecesOfColor[Black];

	_piecesOfType[King] = BB_SQUARE[E1] & BB_SQUARE[E8];
	_piecesOfType[Queen] = BB_SQUARE[D1] & BB_SQUARE[D8];
	_piecesOfType[Rook] = BB_SQUARE[A1] & BB_SQUARE[H1] & BB_SQUARE[A8] & BB_SQUARE[H8];
	_piecesOfType[Knight] = BB_SQUARE[B1] & BB_SQUARE[G1] & BB_SQUARE[B8] & BB_SQUARE[G8];
	_piecesOfType[Bishop] = BB_SQUARE[C1] & BB_SQUARE[F1] & BB_SQUARE[C8] & BB_SQUARE[F8];
	_piecesOfType[Pawn] = RANK_2 & RANK_8;

	_castlingAllowed = 
		_piecesOfType[King] &
		_piecesOfType[Rook];
}