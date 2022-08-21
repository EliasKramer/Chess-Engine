#include "ChessBoard.h"

bool ChessBoard::positionIsValid(Square start, Direction dirToAdd)
{
	return false;
}

UniqueMoveList ChessBoard::getAllPseudoLegalMoves()
{
	UniqueMoveList moveList;

	for (int currSquare = A1; currSquare <= H8; currSquare++)
	{
		//is the same color
		if ((BB_SQUARE[currSquare] & _piecesOfColor[_currentTurnColor]) != 0ULL)
		{
			getMovesOfType(moveList, (Square)currSquare);
		}
	}

	getCastlingMoves(moveList);
	getEnPassantMove(moveList);

	return moveList;
}

PieceType ChessBoard::getTypeAtSquare(Square square)
{
	for (int currType = 0; currType <= NUMBER_OF_DIFFERENT_PIECE_TYPES; currType++)
	{
		if ((BB_SQUARE[square] & _piecesOfType[currType]) != 0ULL)
		{
			return (PieceType)currType;
		}
	}
	return NoPieceType;
}

void ChessBoard::getMovesOfType(UniqueMoveList& moves, Square square)
{
	PieceType type = getTypeAtSquare(square);

	if (type == NoPieceType)
	{
		return;
	}

	switch (type)
	{
	case Pawn:
		getPawnMoves(moves, square);
		break;
	case Knight:
		getKnightMoves(moves, square);
		break;
	case Bishop:
		getBishopMoves(moves, square);
		break;
	case Rook:
		getRookMoves(moves, square);
		break;
	case Queen:
		getQueenMoves(moves, square);
		break;
	case King:
		getKingMoves(moves, square);
		break;
	default:
		break;
	}
}

void ChessBoard::getPawnMoves(UniqueMoveList& moves, Square square)
{
}

void ChessBoard::getKnightMoves(UniqueMoveList& moves, Square square)
{
}

void ChessBoard::getBishopMoves(UniqueMoveList& moves, Square square)
{
}

void ChessBoard::getRookMoves(UniqueMoveList& moves, Square square)
{
}

void ChessBoard::getQueenMoves(UniqueMoveList& moves, Square square)
{
}

void ChessBoard::getKingMoves(UniqueMoveList& moves, Square square)
{
	moves.push_back(std::make_unique<Move>(square, (Square)(square + NORTH)));
	moves.push_back(std::make_unique<Move>(square, (Square)(square + NORTH_EAST)));
	moves.push_back(std::make_unique<Move>(square, (Square)(square + EAST)));
	moves.push_back(std::make_unique<Move>(square, (Square)(square + SOUTH_EAST)));
	moves.push_back(std::make_unique<Move>(square, (Square)(square + SOUTH)));
	moves.push_back(std::make_unique<Move>(square, (Square)(square + SOUTH_WEST)));
	moves.push_back(std::make_unique<Move>(square, (Square)(square + WEST)));
	moves.push_back(std::make_unique<Move>(square, (Square)(square + NORTH_WEST)));
}

void ChessBoard::getCastlingMoves(UniqueMoveList& moves)
{
}

void ChessBoard::getEnPassantMove(UniqueMoveList& moves)
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
