#include "ChessBoard.h"
ChessBoard::ChessBoard()
{
	//at the start kings can castle in each direction
	for (int color = 0; color < 2; color++)
	{
		for (int direction = 0; direction < 2; direction++)
		{
			canCastle[color][direction] = true;
		}
	}

	initBoard();
}

ChessPiece ChessBoard::getAtPosition(Coordinate* coord)
{
	return coord->isValid() ?
		board[coord->getFileAsPosition()][coord->getRankAsPosition()] :
		ChessPiece();
}

std::vector<Move*> ChessBoard::getAllMoves(ChessColor* color)
{
	std::vector<Move*> resultList = std::vector<Move*>();

	short rankForPawnPromotion = *color == ChessColor::White ? 8 : 1;

	for (int file = 0; file < BOARD_SIZE; file++)
	{
		for (int rank = 0; rank < BOARD_SIZE; rank++)
		{
			if (board[file][rank].getColor() == *color)
			{
				Coordinate coord = Coordinate((short)file, (short)rank);
				ChessPiece piece = board[file][rank];
				std::vector<Move*> appendingMoves = getAllMovesOfPiece(&piece, &coord);

				for (Move* currentMove : appendingMoves)
				{
					if (!isInCheck(color, currentMove))
					{
						resultList.push_back(currentMove);
					}
					else {
						delete currentMove;
					}
				}
			}
		}
	}
	return resultList;
}

std::string ChessBoard::toString(ChessColor color)
{
	std::string result = "";

	bool isWhite = color == ChessColor::White;

	int rank = isWhite ? BOARD_SIZE - 1 : 0;
	int rankMax = isWhite ? 0 : BOARD_SIZE;

	result +=
		"  |  A |  B |  C |  D |  E |  F |  G |  H |";
	result +=
		"\n-------------------------------------------\n";

	while (isWhite ? (rank >= rankMax) : (rank < rankMax))
	{
		result += std::to_string(rank + 1);
		result += " | ";
		for (int file = 0; file < BOARD_SIZE; file++)
		{
			ChessColor col = board[file][rank].getColor();
			PieceType type = board[file][rank].getType();

			std::string colorString = getShortNameOfChessColor(&col);
			std::string typeString = getShortNameOfChessType(&type);
			result += colorString + typeString + " | ";
		}

		result +=
			"\n-------------------------------------------\n";

		isWhite ? rank-- : rank++;
	}
	return result;
}

void ChessBoard::updateCastlingAbility(Move* move)
{
	Coordinate start = move->getStart();
	Coordinate dest = move->getDestination();

	//2 iterations - one with 1 and one with 8
	for (short rank = 1; rank <= 8; rank += 7)
	{
		ChessColor currColor = rank == 1 ? ChessColor::White : ChessColor::Black;

		Coordinate kingPos = Coordinate('e', rank);

		//if something gets on the king position or starts from the king position
		//you cant castle no more on both sides
		if (start == kingPos ||
			dest == kingPos)
		{
			setCanCastle(currColor, CastleType::Long, false);
			setCanCastle(currColor, CastleType::Short, false);
		}

		//if something gets on the a rook or the a rook moves you cannot castle long anymore
		Coordinate longRook = Coordinate('a', rank);
		if (start == longRook ||
			dest == longRook)
		{
			setCanCastle(currColor, CastleType::Long, false);
		}

		//if something gets on the h rook or the a rook moves you cannot castle short anymore
		Coordinate shortRook = Coordinate('h', rank);
		if (start == shortRook ||
			dest == shortRook)
		{
			setCanCastle(currColor, CastleType::Short, false);
		}
	}
}

void ChessBoard::setCanCastle(ChessColor col, CastleType cType, bool value)
{
	if (col != ChessColor::NoColor)
	{
		canCastle[col][cType] = value;
	}
}

//returns true unless the king or the rook moved (or rook got taken)
bool ChessBoard::getCanCastle(ChessColor col, CastleType cType)
{
	if (col == ChessColor::NoColor)
	{
		return false;
	}
	return canCastle[col][cType];
}

void ChessBoard::setPieceAt(ChessPiece* piece, Coordinate* coord)
{
	if (coord->isValid())
	{
		int file = coord->getFileAsPosition();
		int rank = coord->getRankAsPosition();
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

void ChessBoard::executeMove(Move* givenMove)
{
	std::function<ChessPiece(Coordinate*)> getAtPos =
		[this](Coordinate* coord) { return getAtPosition(coord); };

	std::function<void(ChessPiece*, Coordinate*)> setAtPos =
		[this](ChessPiece* piece, Coordinate* coord) { return setPieceAt(piece, coord); };

	givenMove->execute(getAtPos, setAtPos);

	setLastMove(givenMove);
	updateCastlingAbility(givenMove);
}

std::vector<Move*> ChessBoard::getAllMovesOfPiece(ChessPiece* piece, Coordinate* coord)
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
	else if (piece->getType() == PieceType::King)
	{
		//add all normal moves of a king
		std::vector<Move*> retVal = executeRayCast(&type, &options, false).getRayCastMoves();
		//add some moves if the king can castle
		addCastleMovesIfPossibleForColor(&col, retVal);
		return retVal;
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
	Coordinate start = move->getStart();
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
	Move m = Move();
	return fieldIsUnderAttack(coord, color, &m);
}

bool ChessBoard::fieldIsUnderAttack(
	Coordinate* coord,
	ChessColor* color,
	Move* madeMove)
{
	RayCastOptions options = RayCastOptions(
		coord,
		false,
		color);

	if (madeMove->isValid())
	{
		if (*coord == madeMove->getStart())
		{
			Coordinate destination = madeMove->getDestination();
			//for pawnattacksfield later
			*coord = destination;
			options.setStart(&destination);
		}
		options.setImaginaryMove(madeMove);
	}

	bool pawnAttacksThisField = fieldGetsAttackedByPawn(coord, color, madeMove);

	RayCastResult raycastResult = RayCastResult();

	options.setMaxIterations(-1);
	//the queen raycast covers the rook and the bishop move sets
	raycastResult = raycastResult + executeQueenRayCast(&options, true);
	options.setMaxIterations(1);
	raycastResult = raycastResult + executeKingRayCast(&options, true);
	raycastResult = raycastResult + executeKnightRayCast(&options, true);

	return pawnAttacksThisField || raycastResult.originPieceIsUnderAttack();
}

bool ChessBoard::isInCheck(ChessColor* col)
{
	Move m = Move();
	return isInCheck(col, &m);
}

bool ChessBoard::isInCheck(ChessColor* col, Move* madeMove)
{
	ChessPiece kingToSearch(PieceType::King, *col);
	Coordinate kingCoord = searchForPiece(&kingToSearch);
	return fieldIsUnderAttack(&kingCoord, col, madeMove);
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
	std::vector<Move*> result = std::vector<Move*>();
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
				result.push_back(new Move(&start, &currentCoord));
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
			result.push_back(new Move(&start, &currentCoord));
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
		Move imaginaryMove = options->getImaginaryMove();

		PieceType type = PieceType::NoType;

		if (options->getMaxIterations() == 1)
		{
			type = PieceType::King;
			calculateIfRayCastResultIsUnderAttackByType(&type, result, &imaginaryMove);
		}
		else {
			type = PieceType::Queen;
			calculateIfRayCastResultIsUnderAttackByType(&type, result, &imaginaryMove);
			type = PieceType::Rook;
			calculateIfRayCastResultIsUnderAttackByType(&type, result, &imaginaryMove);
		}
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
		Move imaginaryMove = options->getImaginaryMove();

		PieceType type = PieceType::NoType;

		if (options->getMaxIterations() == 1)
		{
			type = PieceType::King;
			calculateIfRayCastResultIsUnderAttackByType(&type, result, &imaginaryMove);
		}
		else {
			type = PieceType::Queen;
			calculateIfRayCastResultIsUnderAttackByType(&type, result, &imaginaryMove);
			type = PieceType::Bishop;
			calculateIfRayCastResultIsUnderAttackByType(&type, result, &imaginaryMove);
		}
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
		Move imaginaryMove = options->getImaginaryMove();

		PieceType type = PieceType::Knight;

		calculateIfRayCastResultIsUnderAttackByType(&type, result, &imaginaryMove);
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

void ChessBoard::calculateIfRayCastResultIsUnderAttackByType(PieceType* type, RayCastResult& rcResult, Move* imaginaryMove)
{
	std::function<ChessPiece(Coordinate*, Move*)> getPieceAt =
		[this](Coordinate* coord, Move* move) { return getAtPostitionWithMoveDone(coord, move); };

	rcResult.calculateIfIsUnderAttack(
		type, getPieceAt, imaginaryMove);
}

/*--- Raycasts ---*/

/*--- Castling ---*/
void ChessBoard::addCastleMovesIfPossibleForColor(
	ChessColor* col,
	std::vector<Move*>& moves)
{
	short rank = *col == ChessColor::White ? 1 : 8;

	Coordinate kingCoord = Coordinate('e', rank);
	ChessPiece p = getAtPosition(&kingCoord);

	if (p.isValid() && !fieldIsUnderAttack(&kingCoord, col))
	{
		if (getCanCastle(*col, CastleType::Long))
		{
			Coordinate longCastleOne = Coordinate('d', rank);
			Coordinate longCastleTwo = Coordinate('c', rank);
			Coordinate longCastleThree = Coordinate('b', rank);
			if (fieldIsEmptyAndNotUnderAttack(col, &longCastleOne) &&
				fieldIsEmptyAndNotUnderAttack(col, &longCastleTwo) &&
				!getAtPosition(&longCastleThree).isValid())
			{
				Move secondMove = Move(&Coordinate('a', rank), &Coordinate('d', rank));
				Move* moveToAdd =
					new MoveCastle(&kingCoord, &longCastleTwo, secondMove);
				moves.push_back(moveToAdd);
			}
		}
		if (getCanCastle(*col, CastleType::Short))
		{
			Coordinate shortCastleOne = Coordinate('f', rank);
			Coordinate shortCastleTwo = Coordinate('g', rank);
			if (fieldIsEmptyAndNotUnderAttack(col, &shortCastleOne) &&
				fieldIsEmptyAndNotUnderAttack(col, &shortCastleTwo))
			{
				Move secondMove = Move(&Coordinate('h', rank), &Coordinate('f', rank));
				Move* moveToAdd = new MoveCastle(&kingCoord, &shortCastleTwo, secondMove);
				moves.push_back(moveToAdd);
			}
		}
	}
}

bool ChessBoard::fieldIsEmptyAndNotUnderAttack(ChessColor* col, Coordinate* coord)
{
	if (!getAtPosition(coord).isValid() &&
		!fieldIsUnderAttack(coord, col))
	{
		return true;
	}
	return false;
}
/*--- Castling ---*/

/*--- Pawn Move Set ---*/
std::vector<Move*> ChessBoard::getAllPawnMoves(ChessColor* color, Coordinate* coord)
{
	std::vector<Move*> retVal;
	const short startRank = *color == ChessColor::White ? 2 : 7;

	const short rankMultiplier = *color == ChessColor::White ? 1 : -1;

	const short rankForPromotion = *color == ChessColor::White ? 8 : 1;

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
			else if (rankAdding == 1 &&
				currPosToCheck.getRankAsPosition() == rankForPromotion)
			{
				retVal.push_back(
					new MovePawnPromotion(coord, &currPosToCheck, PieceType::Queen));
				retVal.push_back(
					new MovePawnPromotion(coord, &currPosToCheck, PieceType::Rook));
				retVal.push_back(
					new MovePawnPromotion(coord, &currPosToCheck, PieceType::Bishop));
				retVal.push_back(
					new MovePawnPromotion(coord, &currPosToCheck, PieceType::Knight));
			}
			else
			{
				//new position is empty
				Move* move = new Move(coord, &currPosToCheck);
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
					Move* move = new Move(coord, &targetPos);
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
							Move* move =
								new MoveEnPassant(coord, &targetPos, posOfPieceToTake);
							retVal.push_back(move);
						}
					}
				}
			}
		}
	}

	return retVal;
}

bool ChessBoard::fieldGetsAttackedByPawn(Coordinate* coord, ChessColor* color, Move* madeMove)
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
			ChessPiece pieceAtNewPos = getAtPostitionWithMoveDone(&currCoordToCheck, madeMove);
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
/*--- Pawn Move Set ---*/

