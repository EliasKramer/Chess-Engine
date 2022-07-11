#include "ChessBoard.h"
ChessBoard::ChessBoard()
{
	isWhiteTurn = true;
	initBoard();
}

ChessPiece* ChessBoard::getAtPosition(Coordinate* coord)
{
	return coord->isValid() ?
		&board[coord->getFileAsPosition()][coord->getRankAsPosition()] :
		nullptr;
}

ChessColor* ChessBoard::getTurnColor()
{
	ChessColor white = ChessColor::White;
	ChessColor black = ChessColor::Black;
	return isWhiteTurn ? &white : &black;
}

bool ChessBoard::executeMove(Move* givenMove)
{
	if (givenMove->isValid())
	{
		setPieceAt(
			getAtPosition(
				givenMove->getStart()),
			givenMove->getDestination());
		//set start to invalid
		return true;
	}
	return false;
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

std::list<Move> ChessBoard::getAllMoves()
{
	std::list<Move> resultList;
	return resultList;
}

std::list<Move> ChessBoard::getAllMovesInDirection(
	Coordinate* start,
	ChessColor* color,
	short fileAddingValue,
	short rankAddingValue)
{
	std::list<Move> possibleMoves;
	bool shouldContinue = true;
	Coordinate nextCoord = *start;
	do
	{
		nextCoord = Coordinate(
			(short)((short)nextCoord.getFileAsPosition() + fileAddingValue),
			(short)((short)nextCoord.getRankAsPosition() + rankAddingValue));

		Move moveToCheck = Move(start, &nextCoord);

		shouldContinue = ifCanGoThereAdd(
			color,
			&moveToCheck,
			possibleMoves
		);
	} while (shouldContinue);

	return possibleMoves;
}

std::list<Move> ChessBoard::getAllMovesOfPiece(ChessPiece* piece, Coordinate* coord)
{
	switch (*piece->getType())
	{
	case PieceType::Rook:
		return getAllStraightMoves(piece->getColor(), coord);
	case PieceType::Bishop:
		return getAllDiagonalMoves(piece->getColor(), coord);
	case PieceType::Queen:
		return getAllQueenMoves(piece->getColor(), coord);
	case PieceType::Knight:
		return getAllKnightMoves(piece->getColor(), coord);
	case PieceType::Pawn:
		return getAllPawnMoves(piece->getColor(), coord);
	case PieceType::King:
		return getAllKingMoves(piece->getColor(), coord);
	default:
		return std::list<Move>();
		break;
	}
}

void ChessBoard::setLastMove(Move* move)
{
	lastMove = *move;
}

Move ChessBoard::getLastMove()
{
	//returns value instead of pointer to avoid manipulating it directly
	return lastMove;
}

std::list<Move> ChessBoard::getAllStraightMoves(ChessColor* color, Coordinate* coord)
{
	std::list<Move> possibleMoves;

	possibleMoves.splice(
		possibleMoves.end(),
		getAllMovesInDirection(coord, color, 1, 0));
	possibleMoves.splice(
		possibleMoves.end(),
		getAllMovesInDirection(coord, color, -1, 0));
	possibleMoves.splice(
		possibleMoves.end(),
		getAllMovesInDirection(coord, color, 0, 1));
	possibleMoves.splice(
		possibleMoves.end(),
		getAllMovesInDirection(coord, color, 0, -1));
	return possibleMoves;
}

std::list<Move> ChessBoard::getAllDiagonalMoves(ChessColor* color, Coordinate* coord)
{
	std::list<Move> possibleMoves;

	possibleMoves.splice(
		possibleMoves.end(),
		getAllMovesInDirection(coord, color, 1, 1));
	possibleMoves.splice(
		possibleMoves.end(),
		getAllMovesInDirection(coord, color, -1, 1));
	possibleMoves.splice(
		possibleMoves.end(),
		getAllMovesInDirection(coord, color, 1, -1));
	possibleMoves.splice(
		possibleMoves.end(),
		getAllMovesInDirection(coord, color, -1, -1));
	return possibleMoves;
}
std::list<Move> ChessBoard::getAllQueenMoves(ChessColor* color, Coordinate* coord)
{
	std::list<Move> retVal =
		getAllStraightMoves(color, coord);
	retVal.splice(
		retVal.end(),
		getAllDiagonalMoves(color, coord));
	return retVal;
}

std::list<Move> ChessBoard::getAllKnightMoves(ChessColor* color, Coordinate* coord)
{
	unsigned short file = coord->getFileAsPosition();
	unsigned short rank = coord->getRankAsPosition();
	std::list<Move> retVal;

	short addingVals[8][2] = {
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
		Move moveToCheck = Move(coord, &Coordinate(
			(short)(file + addingVals[i][0]),
			(short)(rank + addingVals[i][1])));

		ifCanGoThereAdd(
			color,
			&moveToCheck,
			retVal);
	}
	return retVal;
}

std::list<Move> ChessBoard::getAllPawnMoves(ChessColor* color, Coordinate* coord)
{
	std::list<Move> retVal;

	const short startRank = *color == ChessColor::White ? 2 : 7;

	const short rankMultiplier = *color == ChessColor::White ? 1 : -1;


	//check moving forward noramlly
	Coordinate oneForward = Coordinate(
		coord->getFileAsPosition(),
		(unsigned short)(coord->getRankAsPosition() + (rankMultiplier * 1)));
	//new position is on the board
	if (oneForward.isValid())
	{
		//new position is empty
		ChessPiece* pieceAtNewPos = getAtPosition(&oneForward);
		if (!pieceAtNewPos->isValid())
		{
			Move move = Move(coord, &oneForward);
			retVal.push_back(move);
		}
	}

	//check moving 2 fields at start
	if (coord->getRankNormal() == startRank)
	{
		Coordinate targetPos = Coordinate(
			coord->getFileAsPosition(),
			(unsigned short)(coord->getRankAsPosition() + (rankMultiplier * 2)));

		//new position is on the board
		if (targetPos.isValid()) //should never be invalid, maybe remove it? idk
		{
			//new position is empty
			ChessPiece* pieceAtNewPos = getAtPosition(&targetPos);

			ChessPiece* pieceBetween = getAtPosition(&oneForward);

			if (!pieceAtNewPos->isValid() && !pieceBetween->isValid())
			{
				Move move = Move(coord, &targetPos);
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
			//new position is empty
			ChessPiece* pieceAtNewPos = getAtPosition(&targetPos);

			if (pieceAtNewPos->isValid())
			{
				if (*pieceAtNewPos->getColor() != *color)
				{
					Move move = Move(coord, &targetPos);
					retVal.push_back(move);
				}
			}
			else {
				//en passant implemenation

				//current piece is on the right rank
				if (coord->getRankNormal() == (*color == White ? 5 : 4))
				{
					Coordinate posOfPieceToTake =
						Coordinate(currentFileAsPos, rankOfCurrentPiece);
					//if the opponent did a move, where i could perform en passant
					//a opposite colored pawn should stand either left or right to my current pawn
					if (
						*getAtPosition(&posOfPieceToTake) ==
						ChessPiece(PieceType::Pawn, (*color == White ? Black : White)))
					{
						//if an that did a double move last turn, i can perform en passant
						const Move lastMoveIfWantToEnPassant = Move(
							&Coordinate(currentFileAsPos, rankOfCurrentPiece + (rankMultiplier * 2)),
							&posOfPieceToTake);

						if (lastMoveIfWantToEnPassant == getLastMove())
						{
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

std::list<Move> ChessBoard::getAllKingMoves(ChessColor* color, Coordinate* coord)
{
	std::list<Move> retVal;

	for (short file = coord->getFileAsPosition() - 1; file <= coord->getFileAsPosition() + 1; file++)
	{
		for (short rank = coord->getRankAsPosition() - 1; rank <= coord->getRankAsPosition() + 1; rank++)
		{
			Coordinate newPos = Coordinate(file, rank);
			Move move = Move(coord, &newPos);

			//the function checks if the move is valid,
			//thus i dont have to check if the current pos is the same as starting pos
			//or if it is valid
			ifCanGoThereAdd(color, &move, retVal);
		}
	}

	return retVal;
}

bool ChessBoard::ifCanGoThereAdd(ChessColor* currColor, Move* move, std::list<Move>& possibleMoves)
{
	//if the move is valid -> start != destination and both coords exist on the board
	if (move->isValid())
	{
		ChessPiece destinationPiece = *getAtPosition(move->getDestination());
		if (destinationPiece.isValid())
		{
			//you cant go to a field where one of your pieces stand
			if ((int)*destinationPiece.getColor() != (int)*currColor)
			{
				possibleMoves.push_back(*move);
			}
			//you can take a piece if it is from the opponent
			return false;
		}
		else {
			//can go to an empty field
			possibleMoves.push_back(*move);
			return true;
		}
	}
	//returns if it should continue the iteration
	return false;
}