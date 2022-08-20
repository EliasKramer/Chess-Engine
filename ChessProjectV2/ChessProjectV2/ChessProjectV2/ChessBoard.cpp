#include "ChessBoard.h"

UniqueMoveList ChessBoard::getAllPseudoLegalMoves()
{
	UniqueMoveList moveList;

	getKingMoves(moveList);

	return moveList;
}

void ChessBoard::getKingMoves(UniqueMoveList& moves)
{
	
}

ChessBoard::ChessBoard()
	:
	_allPieces(BITBOARD_NONE),
	_piecesOfColor{
	BITBOARD_NONE,
	BITBOARD_NONE },

	_piecesOfType{
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE },

	_canCastle{
		{false, false},
		{false, false} },

		_currentTurnColor(White),
		
		_enPassantSquare(SQUARE_NONE),

		_halfMoveClock(0),

		_moveNumber(1)
{}

ChessBoard::ChessBoard(std::string given_fen_code)
	:ChessBoard()
{
	std::string prefixForErrors = "ERROR The given FEN Code is invalid. ";

	std::vector<std::string> split_fen_code = splitString(given_fen_code, ' ');
	if (split_fen_code.size() != 6)
	{
		throw prefixForErrors + "It had not the right size";
	}

	//the implementation of the iteration will be a bit weird,
	//since index 0 is a1 and in the fen code it is a8

	int currRankStartIdx = 56;
	int currFile = 0;

	//fill the board
	for (int currStringIdx = 0;
		currStringIdx < split_fen_code[0].size();
		currStringIdx++)
	{
		char currChar = given_fen_code[currStringIdx];

		int boardPos = currRankStartIdx + currFile;

		if (currChar <= '8' && currChar >= '1')
		{
			int fieldsToSkip = currChar - '0';
			currFile += fieldsToSkip;
		}
		else if (currChar == '/')
		{
			currRankStartIdx -= 8;
			currFile = -1;
			currFile++;
		}
		else {
			BitBoard bbToAdd = BB_SQUARE[boardPos];

			ChessPiece piece(currChar);

			_allPieces |= bbToAdd;
			_piecesOfColor[piece.getColor()] |= bbToAdd;
			_piecesOfType[piece.getType()] |= bbToAdd;
			currFile++;
		}
	}

	//get the turn color
	if (split_fen_code[1].size() != 1)
	{
		throw prefixForErrors + "The turn color should only occupy 1 char";
	}
	_currentTurnColor =
		split_fen_code[1][0] == 'w' ? White :
		split_fen_code[1][0] == 'b' ? Black :
		throw prefixForErrors + "The color could not be found";

	//castling rights
	for (int i = 0; i < split_fen_code[2].size(); i++)
	{
		char currChar = split_fen_code[2][i];

		if (currChar != '-')
		{
			_canCastle
				[getColorOfFenChar(currChar)]
			[getCastlingTypeOfFenChar(currChar)] = true;
		}
	}

	//en passant field
	_enPassantSquare = getSquareFromString(split_fen_code[3]);
	
	//anzahl 50 züge remis regel - 
	//halbzüge seit letzem bauernzug oder schlagen einer figur
	_halfMoveClock = std::stoi(split_fen_code[4]);

	//zugnummer
	_moveNumber = std::stoi(split_fen_code[5]);
}

UniqueMoveList ChessBoard::getAllLegalMoves()
{
	return UniqueMoveList();
}
