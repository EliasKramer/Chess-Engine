#include "ChessBoard.h"
ChessBoard::ChessBoard()
{
	isWhiteTurn = true;
	initBoard();
}

ChessPiece ChessBoard::getAtPosition(Coordinate* coord)
{
	return coord->isValid() ?
		board[coord->getFileAsPosition()][coord->getRankAsPosition()] :
		ChessPiece();
}

ChessColor ChessBoard::getTurnColor()
{
	return isWhiteTurn ? ChessColor::White : ChessColor::Black;
}

std::vector<Move> ChessBoard::getAllMoves()
{
	std::vector<Move> resultList;
	return resultList;
}

void ChessBoard::setPieceAt(ChessPiece* piece, Coordinate* coord)
{
	if (coord->isValid())
	{
		int file = coord->getFileAsPosition();
		int rank = coord->getRankAsPosition();
		ChessPiece toDel = board[file][rank];
		board[file][rank] = *piece;
	}
}

Coordinate ChessBoard::searchForPiece(ChessPiece* piece)
{
	for (short file = 0; file < BOARD_SIZE; file++)
	{
		for (short rank = 0; rank < BOARD_SIZE; rank++)
		{
			if (board[file][rank] == *piece)
			{
				return Coordinate(file, rank);
			}
		}
	}
	return Coordinate();
}

bool ChessBoard::executeMove(Move* givenMove)
{
	if (givenMove->isValid())
	{
		Coordinate start = givenMove->getOrigin();
		Coordinate dest = givenMove->getDestination();

		ChessPiece piece = getAtPosition(
			&start);
		setPieceAt(
			&piece,
			&dest);
		//set start to invalid
		return true;
	}
	return false;
}

std::vector<Move> ChessBoard::getAllMovesOfPiece(ChessPiece* piece, Coordinate* coord)
{
	ChessColor col = piece->getColor();
	PieceType type = piece->getType();
	RayCastOptions options = RayCastOptions(
		coord,
		true,
		&col);

	if (piece->getType() == PieceType::Pawn)
	{
		return getAllPawnMoves(&col, coord);
	}
	else
	{
		return executeRayCast(&type, &options, false).getRayCastMoves();
	}
}

void ChessBoard::setLastMove(Move* move)
{
	lastMove = *move;
}

Move ChessBoard::getLastMove()
{
	return lastMove;
}

ChessPiece ChessBoard::getAtPostitionWithMoveDone(Coordinate* coord, Move* move)
{
	Coordinate start = move->getOrigin();
	Coordinate dest = move->getDestination();

	ChessPiece pieceAtStart = getAtPosition(&start);
	ChessPiece pieceAtDest = getAtPosition(&dest);

	if (move->isValid())
	{
		if (*coord == dest)
		{
			return pieceAtStart;
		}
		else if (*coord == start)
		{
			return ChessPiece();
		}
		else if (pieceAtStart.getType() == PieceType::Pawn &&
			start.getFileAsPosition() != dest.getFileAsPosition() &&
			!pieceAtDest.isValid())
		{
			//en passant handling
			//the check is not that accurate, 
			//because the moves comes only here if it has been checked as valid
			Coordinate enPassantPieceTaken = Coordinate(dest.getFileAsPosition(), start.getRankAsPosition());

			if (*coord == enPassantPieceTaken)
			{
				//if en passant would be performed,
				//and the coord of the piece taken matches the searched one,
				//then return an empty field / invalid chess piece
				return ChessPiece();
			}
		}
		else if (pieceAtStart.getType() == PieceType::King)
		{
			//castling handling here
			short castlingRank = pieceAtStart.getColor() == ChessColor::White ? 1 : 8;
			//king stands on start field
			if (start == Coordinate('e', castlingRank) &&
				dest.getRankNormal() == castlingRank)
			{
				if (dest.getFileNormal() == 'c')
				{
					Move rookMove =
						Move(
							&Coordinate('a', castlingRank),
							&Coordinate('d', castlingRank));
					return getAtPostitionWithMoveDone(coord, &rookMove);
				}
				else if (dest.getFileNormal() == 'g')
				{
					Move rookMove =
						Move(
							&Coordinate('h', castlingRank),
							&Coordinate('f', castlingRank));
					return getAtPostitionWithMoveDone(coord, &rookMove);
				}
			}
		}
	}

	//if the move has no effect on the getting, then just get it like 
	//you would without move
	return getAtPosition(coord);
}

bool ChessBoard::fieldIsUnderAttack(Coordinate* coord, ChessColor* color)
{
	bool pawnAttacksThisField = fieldGetsAttackedByPawn(coord, color);

	RayCastOptions options = RayCastOptions(
		coord,
		false,
		color);

	RayCastResult raycastResult = RayCastResult();
	
	options.setMaxIterations(-1);
	//the queen raycast covers the rook and the bishop move sets
	raycastResult = raycastResult + executeQueenRayCast(&options, true);
	options.setMaxIterations(1);
	raycastResult = raycastResult + executeKingRayCast(&options, true);
	raycastResult = raycastResult + executeKnightRayCast(&options, true);
	
	return pawnAttacksThisField || raycastResult.originPieceIsUnderAttack();
}

bool ChessBoard::colorIsInCheck(ChessColor* col)
{
	ChessPiece kingToSearch(PieceType::King, *col);
	Coordinate kingCoord = searchForPiece(&kingToSearch);
	return fieldIsUnderAttack(&kingCoord, col);
}

void ChessBoard::initBoard()
{
	ChessPiece piece = ChessPiece(PieceType::Rook, ChessColor::White);
	Coordinate position = Coordinate('a', 1);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Knight, ChessColor::White);
	position = Coordinate('b', 1);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Bishop, ChessColor::White);
	position = Coordinate('c', 1);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Queen, ChessColor::White);
	position = Coordinate('d', 1);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::King, ChessColor::White);
	position = Coordinate('e', 1);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Bishop, ChessColor::White);
	position = Coordinate('f', 1);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Knight, ChessColor::White);
	position = Coordinate('g', 1);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Rook, ChessColor::White);
	position = Coordinate('h', 1);
	setPieceAt(&piece, &position);

	for (char file = 'a'; file <= 'h'; file++)
	{
		piece = ChessPiece(PieceType::Pawn, ChessColor::White);
		position = Coordinate(file, 2);
		setPieceAt(&piece, &position);

		piece = ChessPiece(PieceType::NoType, ChessColor::NoColor);
		for (int rank = 3; rank <= 6; rank++)
		{
			position = Coordinate(file, rank);
			setPieceAt(&piece, &position);
		}

		piece = ChessPiece(PieceType::Pawn, ChessColor::Black);
		position = Coordinate(file, 7);
		setPieceAt(&piece, &position);
	}

	piece = ChessPiece(PieceType::Rook, ChessColor::Black);
	position = Coordinate('a', 8);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Knight, ChessColor::Black);
	position = Coordinate('b', 8);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Bishop, ChessColor::Black);
	position = Coordinate('c', 8);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Queen, ChessColor::Black);
	position = Coordinate('d', 8);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::King, ChessColor::Black);
	position = Coordinate('e', 8);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Bishop, ChessColor::Black);
	position = Coordinate('f', 8);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Knight, ChessColor::Black);
	position = Coordinate('g', 8);
	setPieceAt(&piece, &position);

	piece = ChessPiece(PieceType::Rook, ChessColor::Black);
	position = Coordinate('h', 8);
	setPieceAt(&piece, &position);
}

/*--- Raycasts ---*/

RayCastResult ChessBoard::executeSingleRayCast(
	RayCastOptions* options,
	short fileAddingVal,
	short rankAddingVal)
{
	std::vector<Move> result = std::vector<Move>();
	Coordinate start = options->getOrigin();
	Coordinate currentCoord = options->getOrigin();
	short iterationCount = 0;
	short maxIterations = options->getMaxIterations();
	Move imaginaryMove = options->getImaginaryMove();
	do
	{
		iterationCount++;
		currentCoord = Coordinate(
			(short)(currentCoord.getFileAsPosition() + fileAddingVal),
			currentCoord.getRankAsPosition() + rankAddingVal);

		Move currentMoveToCheck = Move(&start, &currentCoord);

		if (!currentCoord.isValid())
		{
			break;
		}

		ChessPiece pieceAtCurrentPos = getAtPostitionWithMoveDone(&currentCoord, &imaginaryMove);

		if (!pieceAtCurrentPos.isValid())
		{
			if (options->getNeedsMoveList())
			{
				//a move to an empty field should only be relevant if
				//you need a move list
				result.push_back(currentMoveToCheck);
			}
		}
		else if (pieceAtCurrentPos.getColor() == options->getColor())
		{
			break;
		}
		else {
			//even if the options do not require list of moves,
			//you should add a move, when it is a capture move.
			//that way, the caller of this function can calculate
			//if the current piece gets attacked or not
			result.push_back(currentMoveToCheck);
			break;
		}

		//should never occur, but it acts as a failsave when a infinite loop happens
		if (iterationCount >= 8)
		{
			throw "A single Raycast should not be longer than 8 iterations.";
		}
	} while (
		((maxIterations == -1) || iterationCount < maxIterations) &&
		currentCoord.isValid());

	return RayCastResult(result);
}

RayCastResult ChessBoard::executeRayCast(
	PieceType* type,
	RayCastOptions* options,
	bool shouldCalculateIfItIsUnderAttack)
{
	switch (*type)
	{
	case PieceType::Pawn:
		throw "can not raycast a pawn move";
	case PieceType::Rook:
		return executeStraightLineRayCast(options, shouldCalculateIfItIsUnderAttack);
	case PieceType::Bishop:
		return executeDiagonalRayCast(options, shouldCalculateIfItIsUnderAttack);
	case PieceType::Queen:
		return executeQueenRayCast(options, shouldCalculateIfItIsUnderAttack);
	case PieceType::Knight:
		return executeKnightRayCast(options, shouldCalculateIfItIsUnderAttack);
	case PieceType::King:
		return executeKingRayCast(options, shouldCalculateIfItIsUnderAttack);
	default:
		throw "should have found a piece type";
		break;
	}
	return RayCastResult();
}

RayCastResult ChessBoard::executeStraightLineRayCast(RayCastOptions* options, bool shouldCalculateIfItIsUnderAttack)
{
	RayCastResult result = RayCastResult();

	//do 2 iterrations. one time with -1 and one time with 1
	for (short addingVal = -1; addingVal <= 1; addingVal += 2)
	{
		result = result + executeSingleRayCast(
			options,
			addingVal,
			0);
		result = result + executeSingleRayCast(
			options,
			0,
			addingVal);
	}

	if (shouldCalculateIfItIsUnderAttack)
	{
		std::function<ChessPiece(Coordinate*)> getPieceAt =
			[this](Coordinate* coord) { return getAtPosition(coord); };

		// a queen can also attack the way a rook does,
		// so if it gets hit by the raycast it attacks the current field
		PieceType queenType = PieceType::Queen;
		PieceType rookType = PieceType::Rook;
		std::vector<PieceType*> typesThatCanAttackTheOriginField = {
			&queenType,
			&rookType
		};
		if (options->getMaxIterations() == 1)
		{
			PieceType kingType = PieceType::King;
			typesThatCanAttackTheOriginField.push_back(&kingType);
		}
		result.calculateIfIsUnderAttack(
			typesThatCanAttackTheOriginField, getPieceAt);

	}

	return result;
}

RayCastResult ChessBoard::executeDiagonalRayCast(RayCastOptions* options, bool shouldCalculateIfItIsUnderAttack)
{
	RayCastResult result = RayCastResult();

	//do 4 iterrations
	//-1 -1
	//-1 +1
	//+1 -1
	//+1 +1
	for (short fileAddingVal = -1; fileAddingVal <= 1; fileAddingVal += 2)
	{
		for (short rankAddingVal = -1; rankAddingVal <= 1; rankAddingVal += 2)
		{
			result = result + executeSingleRayCast(
				options,
				fileAddingVal,
				rankAddingVal);
		}
	}
	if (shouldCalculateIfItIsUnderAttack)
	{
		std::function<ChessPiece(Coordinate*)> getPieceAt =
			[this](Coordinate* coord) { return getAtPosition(coord); };

		// a queen can also attack the way a bishop does,
		// so if it gets hit by the raycast it attacks the current field
		PieceType queenType = PieceType::Queen;
		PieceType bishopType = PieceType::Bishop;
		std::vector<PieceType*> typesThatCanAttackTheOriginField = {
			&queenType,
			&bishopType
		};
		if (options->getMaxIterations() == 1)
		{
			PieceType kingType = PieceType::King;
			typesThatCanAttackTheOriginField.push_back(&kingType);
		}

		result.calculateIfIsUnderAttack(
			typesThatCanAttackTheOriginField, getPieceAt);
	}
	return result;
}

RayCastResult ChessBoard::executeQueenRayCast(RayCastOptions* options, bool shouldCalculateIfItIsUnderAttack)
{
	options->setMaxIterations(-1);
	return
		executeDiagonalRayCast(options, shouldCalculateIfItIsUnderAttack) +
		executeStraightLineRayCast(options, shouldCalculateIfItIsUnderAttack);
}

RayCastResult ChessBoard::executeKnightRayCast(RayCastOptions* options, bool shouldCalculateIfItIsUnderAttack)
{
	RayCastResult result = RayCastResult();

	options->setMaxIterations(1);

	const short addingVals[8][2] = {
		{ 1, 2 },
		{ 2, 1 },
		{ 2, -1 },
		{ 1, -2 },
		{ -1, -2 },
		{ -2, -1 },
		{ -2, 1 },
		{ -1, 2 }
	};

	for (int i = 0; i < 8; i++)
	{
		result = result + executeSingleRayCast(
			options,
			addingVals[i][0],
			addingVals[i][1]);
	}

	if (shouldCalculateIfItIsUnderAttack)
	{
		std::function<ChessPiece(Coordinate*)> getPieceAt =
			[this](Coordinate* coord) { return getAtPosition(coord); };
		PieceType knightType = PieceType::Knight;

		result.calculateIfIsUnderAttack(
			&knightType, getPieceAt);
	}
	return result;
}

RayCastResult ChessBoard::executeKingRayCast(RayCastOptions* options, bool shouldCalculateIfItIsUnderAttack)
{
	options->setMaxIterations(1);
	return
		executeDiagonalRayCast(options, shouldCalculateIfItIsUnderAttack) +
		executeStraightLineRayCast(options, shouldCalculateIfItIsUnderAttack);
}

/*--- Raycasts ---*/

std::vector<Move> ChessBoard::getAllPawnMoves(ChessColor* color, Coordinate* coord)
{
	std::vector<Move> retVal;
	const short startRank = *color == ChessColor::White ? 2 : 7;

	const short rankMultiplier = *color == ChessColor::White ? 1 : -1;

	//checking for moves forward
	//loop has alway 2 iterations -> checks 1 and 2 fields forwards
	for (int rankAdding = 1; rankAdding <= 2; rankAdding++)
	{
		Coordinate currPosToCheck = Coordinate(
			coord->getFileAsPosition(),
			(short)(coord->getRankAsPosition() + (rankMultiplier * rankAdding)));

		//new position is on the board
		//if a pawn wants to go 2 fields it has to be at the start rank
		if (currPosToCheck.isValid() &&
			(rankAdding != 2 || coord->getRankNormal() == startRank))
		{
			ChessPiece pieceAtNewPos = getAtPosition(&currPosToCheck);
			if (pieceAtNewPos.isValid())
			{
				//no need going forward another time, if path is blocked
				break;
			}
			else {
				//new position is empty
				Move move = Move(coord, &currPosToCheck);
				retVal.push_back(move);
			}
		}
	}

	//checking if you can attack a piece
	//loop has always 2 iterations -> once with -1 and once with 1
	for (short fileAddingValue = -1; fileAddingValue <= 1; fileAddingValue += 2)
	{
		const short currentFileAsPos = (short)(coord->getFileAsPosition() + fileAddingValue);
		const short rankOfCurrentPiece = (short)(coord->getRankAsPosition());
		//new pos is 1 field in direction where the piece is headed 
		//and once on 1 field either left or right (depending on what iteration of the loop it is)
		Coordinate targetPos = Coordinate(
			currentFileAsPos,
			rankOfCurrentPiece + (rankMultiplier * 1));

		//new position is on the board
		if (targetPos.isValid())
		{
			ChessPiece pieceAtNewPos = getAtPosition(&targetPos);

			//if there is a piece at the currently check position
			if (pieceAtNewPos.isValid())
			{
				//if the piece is of the opposite color
				if (pieceAtNewPos.getColor() != *color)
				{
					//the move is valid and can be done
					Move move = Move(coord, &targetPos);
					retVal.push_back(move);
				}
			}
			//if one field diagonal in front is free
			else {
				//en passant implemenation

				//current piece is on the right rank to perform en passant
				if (coord->getRankNormal() == (*color == White ? 5 : 4))
				{
					Coordinate posOfPieceToTake =
						Coordinate(currentFileAsPos, rankOfCurrentPiece);

					//if the opponent did a move, where i could perform en passant
					//a opposite colored pawn should stand either left or right to my current pawn
					if (
						getAtPosition(&posOfPieceToTake) ==
						ChessPiece(PieceType::Pawn, (*color == White ? Black : White)))
					{
						//if that very pawn next to the current pawn did do a double move last turn
						const Move lastMoveIfWantToEnPassant = Move(
							&Coordinate(currentFileAsPos, rankOfCurrentPiece + (rankMultiplier * 2)),
							&posOfPieceToTake);

						if (lastMoveIfWantToEnPassant == getLastMove())
						{
							//the en passant move is possible
							Move move = Move(coord, &targetPos);
							retVal.push_back(move);
						}
					}
				}
			}
		}
	}

	return retVal;
}

bool ChessBoard::fieldGetsAttackedByPawn(Coordinate* coord, ChessColor* color)
{
	PieceType pawnType = PieceType::Pawn;
	//coord is valid is already checked by caller
	short rankAddingValue = *color == ChessColor::White ? 1 : -1;

	for (short fileAddingValue = -1; fileAddingValue <= 1; fileAddingValue += 2)
	{
		Coordinate currCoordToCheck = Coordinate(
			(short)(coord->getFileAsPosition() + fileAddingValue),
			(short)(coord->getRankAsPosition() + rankAddingValue));
		
		if (currCoordToCheck.isValid())
		{
			ChessPiece pieceAtNewPos = getAtPosition(&currCoordToCheck);
			if (pieceAtNewPos.isValid() &&
				pieceAtNewPos.getType() == pawnType &&
				pieceAtNewPos.getColor() != *color)
			{
				return true;
			}
		}
	}
	return false;
}

