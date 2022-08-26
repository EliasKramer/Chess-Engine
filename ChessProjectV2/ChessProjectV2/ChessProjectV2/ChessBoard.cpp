#include "ChessBoard.h"

bool ChessBoard::destinationIsOnBoard(Square start, Direction direction)
{
	//if the invalid board for the direction and
	//the start square dont overlap then the new pos is valid
	return (INVALID_FIELDS_FOR_DIR.at(direction) & BB_SQUARE[start]) == 0;
}

bool ChessBoard::destinationIsSameColor(Square start, Direction direction, ChessColor color)
{
	int newPos = (start + direction);

	if (newPos < A1 || newPos > H8)
	{
		return false;
	}

	return positionIsSameColor((Square)newPos, color);
}

bool ChessBoard::positionIsSameColor(Square pos, ChessColor color)
{
	return (_piecesOfColor[color] & BB_SQUARE[pos]) != 0;
}

void ChessBoard::addIfDestinationIsValid(MoveList& moves, Square start, Direction dir, PieceType type)
{
	if (destinationIsOnBoard(start, dir))
	{
		if (!destinationIsSameColor(start, dir, _currentTurnColor))
		{
			moves.push_back(Move(start, (Square)(start + dir), type));
		}
	}
}

void ChessBoard::addIfDestinationIsColor(
	MoveList& moves,
	Square start,
	Direction dir,
	ChessColor color,
	PieceType type)
{
	if (destinationIsOnBoard(start, dir))
	{
		Square newPos = (Square)(start + dir);
		if (positionIsSameColor(newPos, color))
		{
			moves.push_back(Move(start, newPos, type));
		}
	}
}

MoveList ChessBoard::getAllPseudoLegalMoves()
{
	MoveList moveList;

	getPawnMoves(moveList);
	getKnightMoves(moveList);
	getBishopMoves(moveList);
	getRookMoves(moveList);
	getQueenMoves(moveList);
	getKingMoves(moveList);

	getCastlingMoves(moveList);
	getEnPassantMove(moveList);

	return moveList;
}

void ChessBoard::getPawnMoves(MoveList& moves)
{
	Direction forward = getForwardForColor(_currentTurnColor);
	BitBoard startRank = _currentTurnColor == White ? RANK_2 : RANK_7;

	for (uint8_t currSquareIdx = A1; currSquareIdx <= H8; currSquareIdx++)
	{
		Square currSquare = (Square)currSquareIdx;
		BitBoard piecePosBB = BB_SQUARE[currSquareIdx];

		//if the current square is a pawn and the same color
		if ((piecePosBB &
			_piecesOfType[Pawn] &
			_piecesOfColor[_currentTurnColor]) != 0ULL)
		{
			Square forwardPos = (Square)(currSquare + forward);
			BitBoard forwardPosBB = BB_SQUARE[forwardPos];
			//one move forward
			if (destinationIsOnBoard(currSquare, forward) &&
				(forwardPosBB & _allPieces) == 0ULL)
			{
				moves.push_back(Move(currSquare, forwardPos, Pawn));
				//TODO
				//if move ends on promotion rank it should be a promotion move

				//two moves forward (only possible if one move is possible
				Square doubleForward = (Square)(forwardPos + forward);
				if ((piecePosBB & startRank) != 0 &&
					destinationIsOnBoard(forwardPos, forward) &&
					(BB_SQUARE[doubleForward] & _allPieces) == 0ULL)
				{
					//TODO
					//setting the en passant square
					moves.push_back(Move(currSquare, doubleForward, Pawn));
				}
			}

			//taking diagonal checks
			//this loop checks one time left and one time right
			Direction leftAndRight[2] = { WEST, EAST };
			for (int i = 0; i < 2; i++)
			{
				Direction direction = (Direction)(leftAndRight[i] + forward);
				ChessColor opponentColor = getOppositeColor(_currentTurnColor);
				addIfDestinationIsColor(moves, currSquare, direction, opponentColor, Pawn);
			}
		}
	}
}

void ChessBoard::getKnightMoves(MoveList& moves)
{
	for (uint8_t currSquareIdx = A1; currSquareIdx <= H8; currSquareIdx++)
	{
		if ((BB_SQUARE[currSquareIdx] &
			_piecesOfType[Knight] &
			_piecesOfColor[_currentTurnColor]) != 0ULL)
		{
			addIfDestinationIsValid(moves, (Square)currSquareIdx, NORTH_NORTH_EAST, Knight);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, EAST_NORTH_EAST, Knight);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, EAST_SOUTH_EAST, Knight);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, SOUTH_SOUTH_EAST, Knight);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, SOUTH_SOUTH_WEST, Knight);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, WEST_SOUTH_WEST, Knight);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, WEST_NORTH_WEST, Knight);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, NORTH_NORTH_WEST, Knight);
		}
	}
}

void ChessBoard::getBishopMoves(MoveList& moves)
{
	const int numberOfDirections = 4;
	Direction directions[numberOfDirections] =
	{ NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST };

	for (uint8_t currSquareIdx = A1; currSquareIdx <= H8; currSquareIdx++)
	{
		if ((BB_SQUARE[currSquareIdx] &
			_piecesOfType[Bishop] &
			_piecesOfColor[_currentTurnColor]) != 0ULL)
		{
			addRayMoves(moves, (Square)currSquareIdx, Bishop, directions, numberOfDirections);
		}
	}

}

void ChessBoard::getRookMoves(MoveList& moves)
{
	const int numberOfDirections = 4;
	Direction directions[numberOfDirections] =
	{ NORTH, EAST, SOUTH, WEST };

	for (uint8_t currSquareIdx = A1; currSquareIdx <= H8; currSquareIdx++)
	{
		if ((BB_SQUARE[currSquareIdx] &
			_piecesOfType[Rook] &
			_piecesOfColor[_currentTurnColor]) != 0ULL)
		{
			addRayMoves(moves, (Square)currSquareIdx, Rook, directions, numberOfDirections);
		}
	}
}

void ChessBoard::getQueenMoves(MoveList& moves)
{
	const int numberOfDirections = 8;
	Direction directions[numberOfDirections] =
	{ NORTH, EAST, SOUTH, WEST, NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST };

	for (uint8_t currSquareIdx = A1; currSquareIdx <= H8; currSquareIdx++)
	{
		if ((BB_SQUARE[currSquareIdx] &
			_piecesOfType[Queen] &
			_piecesOfColor[_currentTurnColor]) != 0ULL)
		{
			addRayMoves(moves, (Square)currSquareIdx, Queen, directions, numberOfDirections);
		}
	}
}

void ChessBoard::getKingMoves(MoveList& moves)
{
	for (uint8_t currSquareIdx = A1; currSquareIdx <= H8; currSquareIdx++)
	{
		if ((BB_SQUARE[currSquareIdx] &
			_piecesOfType[King] &
			_piecesOfColor[_currentTurnColor]) != 0ULL)
		{
			addIfDestinationIsValid(moves, (Square)currSquareIdx, NORTH, King);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, NORTH_EAST, King);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, EAST, King);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, SOUTH_EAST, King);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, SOUTH, King);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, SOUTH_WEST, King);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, WEST, King);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, NORTH_WEST, King);
		}
	}
}

void ChessBoard::getCastlingMoves(MoveList& moves)
{
}

void ChessBoard::getEnPassantMove(MoveList& moves)
{
}

void ChessBoard::addRayMoves(
	MoveList& moves,
	Square start,
	PieceType type,
	Direction directions[],
	int numberOfDirections)
{
	ChessColor opponentColor = getOppositeColor(_currentTurnColor);

	for (int i = 0; i < numberOfDirections; i++)
	{
		Direction currentDirection = directions[i];

		Square currentSquare = start;
		while (true)
		{
			//if the new position would be on the board
			if (destinationIsOnBoard(currentSquare, currentDirection))
			{
				//set the new position
				currentSquare = (Square)(currentSquare + currentDirection);

				//if the new position is the same color as the piece to check
				if (positionIsSameColor(currentSquare, _currentTurnColor))
				{
					//you cannot go on a square where a piece of the same color is
					break;
				}
				else if (positionIsSameColor(currentSquare, opponentColor))
				{
					//if an opponent is on the new field you can take him,
					//but cannot continue after that (you cannot jump over opponents)
					moves.push_back(Move(start, currentSquare, type));
					break;
				}
				else {
					//if there is no piece at the new position you can move there.
					moves.push_back(Move(start, currentSquare, type));
				}
			}
			else {
				//if the new position is not on the board, the search should not continue
				break;
			}
		}
	}
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

	//50 move rule
	_halfMoveClock = std::stoi(split_fen_code[4]);

	//move number
	_moveNumber = std::stoi(split_fen_code[5]);
}

MoveList ChessBoard::getAllLegalMoves()
{
	return MoveList();
}
