#include "ChessBoard.h"

void ChessBoard::copySquare(Square copyField, Square pasteField)
{
	BitBoard copyPos = BB_SQUARE[copyField];
	BitBoard pastePos = BB_SQUARE[pasteField];

	for (int i = 0; i < DIFFERENT_CHESS_COLORS; i++)
	{
		ChessColor currCol = (ChessColor)i;

		if ((_piecesOfColor[currCol] & copyPos) != 0)
		{
			_piecesOfColor[currCol] = _piecesOfColor[currCol] | pastePos;
		}
	}

	for (int i = 0; i < NUMBER_OF_DIFFERENT_PIECE_TYPES; i++)
	{
		PieceType currType = (PieceType)i;

		if ((_piecesOfType[currType] & copyPos) != 0)
		{
			_piecesOfType[currType] = _piecesOfType[currType] | pastePos;
		}
	}

	if ((_allPieces & copyPos) != 0)
	{
		_allPieces = _allPieces | pastePos;
	}
}

void ChessBoard::setAtPosition(ChessPiece piece, Square position)
{
	BitBoard piecePos = BB_SQUARE[position];

	_allPieces = _allPieces | piecePos;

	ChessColor col = piece.getColor();
	_piecesOfColor[col] = _piecesOfColor[col] | piecePos;

	PieceType type = piece.getType();
	_piecesOfType[type] = _piecesOfType[type] | piecePos;
}

void ChessBoard::delAtPos(Square position)
{
	BitBoard keepPiecesMask = ~(BB_SQUARE[position]);

	_allPieces = _allPieces & keepPiecesMask;

	for (int i = 0; i < DIFFERENT_CHESS_COLORS; i++)
	{
		ChessColor currCol = (ChessColor)i;
		_piecesOfColor[currCol] = _piecesOfColor[currCol] & keepPiecesMask;
	}

	for (int i = 0; i < NUMBER_OF_DIFFERENT_PIECE_TYPES; i++)
	{
		PieceType currType = (PieceType)i;
		_piecesOfType[currType] = _piecesOfType[currType] & keepPiecesMask;
	}
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

void ChessBoard::addIfDestinationIsValid(UniqueMoveList& moves, Square start, Direction dir)
{
	if (destinationIsOnBoard(start, dir))
	{
		if (!destinationIsSameColor(start, dir, _currentTurnColor))
		{
			moves.push_back(std::make_unique<Move>(start, (Square)(start + dir)));
		}
	}
}

void ChessBoard::addIfDestinationIsColor(
	UniqueMoveList& moves,
	Square start,
	Direction dir,
	ChessColor color)
{
	if (destinationIsOnBoard(start, dir))
	{
		Square newPos = (Square)(start + dir);
		if (positionIsSameColor(newPos, color))
		{
			moves.push_back(std::make_unique<Move>(start, newPos));
		}
	}
}

UniqueMoveList ChessBoard::getAllPseudoLegalMoves()
{
	UniqueMoveList moveList;

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

BitBoard ChessBoard::getKingCheckRayCast()
{
	return BitBoard();
}

void ChessBoard::getPawnMoves(UniqueMoveList& moves)
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
				addPawnMove(moves, currSquare, forwardPos);
				//moves.push_back(std::make_unique<Move>(currSquare, forwardPos));
				//TODO
				//if move ends on promotion rank it should be a promotion move

				//two moves forward (only possible if one move is possible
				Square doubleForward = (Square)(forwardPos + forward);
				if ((piecePosBB & startRank) != 0 &&
					destinationIsOnBoard(forwardPos, forward) &&
					(BB_SQUARE[doubleForward] & _allPieces) == 0ULL)
				{
					moves.push_back(std::make_unique<Move>(currSquare, doubleForward));
				}
			}

			//taking diagonal checks
			//this loop checks one time left and one time right
			Direction leftAndRight[2] = { WEST, EAST };
			for (int i = 0; i < 2; i++)
			{
				Direction direction = (Direction)(leftAndRight[i] + forward);
				ChessColor opponentColor = getOppositeColor(_currentTurnColor);

				if (destinationIsSameColor(currSquare, direction, opponentColor)
					&& destinationIsOnBoard(currSquare, direction))
				{
					addPawnMove(moves, currSquare, (Square)(currSquare + direction));
				}
			}
		}
	}
}

void ChessBoard::getKnightMoves(UniqueMoveList& moves)
{
	for (uint8_t currSquareIdx = A1; currSquareIdx <= H8; currSquareIdx++)
	{
		if ((BB_SQUARE[currSquareIdx] &
			_piecesOfType[Knight] &
			_piecesOfColor[_currentTurnColor]) != 0ULL)
		{
			addIfDestinationIsValid(moves, (Square)currSquareIdx, NORTH_NORTH_EAST);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, EAST_NORTH_EAST);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, EAST_SOUTH_EAST);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, SOUTH_SOUTH_EAST);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, SOUTH_SOUTH_WEST);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, WEST_SOUTH_WEST);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, WEST_NORTH_WEST);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, NORTH_NORTH_WEST);
		}
	}
}

void ChessBoard::getBishopMoves(UniqueMoveList& moves)
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
			addRayMoves(moves, (Square)currSquareIdx, directions, numberOfDirections);
		}
	}

}

void ChessBoard::getRookMoves(UniqueMoveList& moves)
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
			addRayMoves(moves, (Square)currSquareIdx, directions, numberOfDirections);
		}
	}
}

void ChessBoard::getQueenMoves(UniqueMoveList& moves)
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
			addRayMoves(moves, (Square)currSquareIdx, directions, numberOfDirections);
		}
	}
}

void ChessBoard::getKingMoves(UniqueMoveList& moves)
{
	for (uint8_t currSquareIdx = A1; currSquareIdx <= H8; currSquareIdx++)
	{
		if ((BB_SQUARE[currSquareIdx] &
			_piecesOfType[King] &
			_piecesOfColor[_currentTurnColor]) != 0ULL)
		{
			addIfDestinationIsValid(moves, (Square)currSquareIdx, NORTH);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, NORTH_EAST);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, EAST);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, SOUTH_EAST);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, SOUTH);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, SOUTH_WEST);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, WEST);
			addIfDestinationIsValid(moves, (Square)currSquareIdx, NORTH_WEST);
		}
	}
}

void ChessBoard::addPawnMove(UniqueMoveList& moves, Square start, Square dest)
{
	BitBoard promotionRank = _currentTurnColor == White ? RANK_8 : RANK_1;

	if ((BB_SQUARE[dest] & promotionRank) != 0ULL)
	{
		moves.push_back(std::make_unique<MovePromote>(start, dest, Queen));
		moves.push_back(std::make_unique<MovePromote>(start, dest, Rook));
		moves.push_back(std::make_unique<MovePromote>(start, dest, Bishop));
		moves.push_back(std::make_unique<MovePromote>(start, dest, Knight));
	}
	else
	{
		moves.push_back(std::make_unique<Move>(start, dest));
	}
}

void ChessBoard::getCastlingMoves(UniqueMoveList& moves)
{
	//TODO
	//_canCastle[_currentTurnColor][CastleLong] = true;
	//_canCastle[_currentTurnColor][CastleShort] = true;
}

void ChessBoard::getEnPassantMove(UniqueMoveList& moves)
{
	if (_enPassantSquare == SQUARE_NONE)
	{
		return;
	}

	Direction backwards = getBackwardForColor(_currentTurnColor);

	Direction directionsWhereOwnPawnCouldBe[2] =
	{ (Direction)(backwards + EAST), (Direction)(backwards + WEST) };

	for (int i = 0; i < 2; i++)
	{
		if (destinationIsOnBoard(_enPassantSquare, directionsWhereOwnPawnCouldBe[i]))
		{
			Square ownPawnPos = (Square)(_enPassantSquare + directionsWhereOwnPawnCouldBe[i]);
			if ((BB_SQUARE[ownPawnPos] & _piecesOfColor[_currentTurnColor] & _piecesOfType[Pawn]) != 0ULL)
			{
				Square pawnPosToDelete = (Square)(_enPassantSquare + backwards);
				moves.push_back(std::make_unique<MoveEnPassant>(
					ownPawnPos, _enPassantSquare,
					pawnPosToDelete));
			}
		}
	}
}

void ChessBoard::addRayMoves(
	UniqueMoveList& moves,
	Square start,
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
					moves.push_back(std::make_unique<Move>(start, currentSquare));
					break;
				}
				else {
					//if there is no piece at the new position you can move there.
					moves.push_back(std::make_unique<Move>(start, currentSquare));
				}
			}
			else {
				//if the new position is not on the board, the search should not continue
				break;
			}
		}
	}
}

bool ChessBoard::fieldIsUnderAttack(Square pos)
{
	//is only used for king checks and castling, so no en passant implemented

	ChessColor opponentColor = getOppositeColor(_currentTurnColor);

	//gets attacked by knight
	if ((KNIGHT_ATTACK_BB[pos] &
		_piecesOfColor[opponentColor] &
		_piecesOfType[Knight]) != 0ULL)
	{
		return true;
	}

	//gets attacked by pawn
	//it is handled like the current field is a pawn, 
	//because if the current field has a pawn on its attacking squares, 
	//it can also be attacked by the opponent pawn
	if ((PAWN_ATTACK_BB[_currentTurnColor][pos] &
		_piecesOfColor[opponentColor] &
		_piecesOfType[Pawn]) != 0ULL)
	{
		return true;
	}

	//field gets attacked by king
	if ((KING_ATTACKS_BB[pos] &
		_piecesOfColor[opponentColor] &
		_piecesOfType[King]) != 0ULL)
	{
		return true;
	}

	//raycast in every direction and check for queen, rook or bishop attacks
	return fieldGetsAttackedBySlidingPiece(pos);
}

bool ChessBoard::fieldIsUnderAttackWithMoveDone(Square pos, Move* move)
{
	return false;
}

bool ChessBoard::fieldGetsAttackedBySlidingPiece(Square pos)
{
	ChessColor opponentColor = getOppositeColor(_currentTurnColor);

	for (int i = 0; i < 8; i++)
	{
		Direction currentDirection = ALL_SLIDING_DIRECTIONS[i];

		Square currentSquare = pos;
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
					BitBoard currPosBB = BB_SQUARE[currentSquare];

					bool currDirIsDiagonal = i > 3;

					//found piece is a queen -> will attack no matter in which direction you are sliding
					if ((currPosBB & _piecesOfType[Queen]) != 0ULL)
					{
						//is queen
						return true;
					}
					//if found piece is a rook or a bishop, sliding direction matters
					else if (currDirIsDiagonal)
					{
						if ((currPosBB & _piecesOfType[Bishop]) != 0ULL)
						{
							//is bishop
							return true;
						}
					}
					else
					{
						if ((currPosBB & _piecesOfType[Rook]) != 0ULL)
						{
							//is rook
							return true;
						}
					}
					//if the found piece is an enemy, but no sliding piece then it does not attack you
					break;
				}
			}
			else 
			{
				//if the new position is not on the board, the search should not continue
				break;
			}
		}
	}
	return false;
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
