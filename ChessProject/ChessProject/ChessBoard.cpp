#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
	isWhiteTurn = true;
	initBoard();
}

ChessPiece* ChessBoard::getAtPosition(Coordinate* coord)
{
	return coord->isValid() ?
		&board[coord->getFileAsPosition()][ coord->getRankAsPosition()] :
		nullptr;
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

	for(char file = 'a'; file <= 'h'; file++)
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