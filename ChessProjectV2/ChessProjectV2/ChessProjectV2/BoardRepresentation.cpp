#include "BoardRepresentation.h"

BoardRepresentation::BoardRepresentation()
	:
	all_pieces(BITBOARD_NONE),
	pieces_of_color{
	BITBOARD_NONE,
	BITBOARD_NONE },

	pieces_of_type{
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE,
	BITBOARD_NONE },
	
	king_pos{E1, E8}
{}

ChessPiece BoardRepresentation::get_piece_at(Square square) const
{
	BitBoard squareBB = BB_SQUARE[square];
	//can be improved by adding null types
	ChessColor colFound = no_color;
	PieceType typeFound = no_type;

	for (int i = 0; i < DIFFERENT_CHESS_COLORS; i++)
	{
		ChessColor currCol = (ChessColor)i;

		if (bitboards_overlap(pieces_of_color[currCol], squareBB))
		{
			colFound = currCol;
			break;
		}
	}
	for (int i = 0; i < NUMBER_OF_DIFFERENT_PIECE_TYPES; i++)
	{
		PieceType currType = (PieceType)i;

		if (bitboards_overlap(pieces_of_type[currType], squareBB))
		{
			typeFound = currType;
			break;
		}
	}

	return ChessPiece(colFound, typeFound);
}

void BoardRepresentation::set_at_position(ChessPiece piece, Square position)
{
	if(piece.get_type() == king)
	{
		king_pos[piece.get_color()] = position;
	}

	piece_positions[piece.get_color()][piece.get_type()].push_back(position);

	set_piece_bitboard(piece, BB_SQUARE[position]);
}

void BoardRepresentation::del_at_pos(Square position)
{
	BitBoard keepPiecesMask = ~(BB_SQUARE[position]);

	all_pieces = all_pieces & keepPiecesMask;

	for (int i = 0; i < DIFFERENT_CHESS_COLORS; i++)
	{
		ChessColor currCol = (ChessColor)i;
		pieces_of_color[currCol] = pieces_of_color[currCol] & keepPiecesMask;
	}

	for (int i = 0; i < NUMBER_OF_DIFFERENT_PIECE_TYPES; i++)
	{
		PieceType currType = (PieceType)i;
		pieces_of_type[currType] = pieces_of_type[currType] & keepPiecesMask;
	}

	remove_all_from_piece_list_at(position);
}

void BoardRepresentation::move_from_pos_to_pos(Square start, Square destination)
{
	BitBoard startPosBB = BB_SQUARE[start];
	BitBoard destPosBB = BB_SQUARE[destination];

	ChessPiece startPiece = get_piece_at(start);
	ChessPiece destPiece = get_piece_at(destination);

	//if there is not piece to move return
	if (!startPiece.is_valid())
	{
		return;
	}
	if (destPiece.is_valid())
	{
		del_at_pos(destination);
	}

	//add piece to the color bitboard
	pieces_of_color[startPiece.get_color()] = pieces_of_color[startPiece.get_color()] | destPosBB;
	//add piece to the type bitboard
	pieces_of_type[startPiece.get_type()] = pieces_of_type[startPiece.get_type()] | destPosBB;
	//add piece to the all bitbaord
	all_pieces = all_pieces | destPosBB;

	del_at_pos(start);
}

void BoardRepresentation::set_piece_bitboard(ChessPiece piece, BitBoard bitboard)
{
	all_pieces = all_pieces | bitboard;

	ChessColor col = piece.get_color();
	pieces_of_color[col] = pieces_of_color[col] | bitboard;

	PieceType type = piece.get_type();
	pieces_of_type[type] = pieces_of_type[type] | bitboard;
}

void BoardRepresentation::remove_from_piece_list(ChessPiece piece, Square position)
{
	std::vector<Square>& pieceList = piece_positions[piece.get_color()][piece.get_type()];

	for (int i = 0; i < pieceList.size(); i++)
	{
		if (pieceList[i] == position)
		{
			pieceList.erase(pieceList.begin() + i);
			break;
		}
	}
}

void BoardRepresentation::remove_all_from_piece_list_at(Square position)
{
	for (int i = 0; i < DIFFERENT_CHESS_COLORS; i++)
	{
		ChessColor currCol = (ChessColor)i;
		
		for (int j = 0; j < NUMBER_OF_DIFFERENT_PIECE_TYPES; j++)
		{
			PieceType currType = (PieceType)j;

			remove_from_piece_list(ChessPiece(currCol, currType), position);
		}
	}
}

//Equals Operator

bool operator==(const BoardRepresentation& first, const BoardRepresentation& second)
{
	bool retVal = first.all_pieces == second.all_pieces
		&& (first.pieces_of_color[white] == second.pieces_of_color[white])
		&& (first.pieces_of_color[black] == second.pieces_of_color[black]);

	for (int i = 0; i < NUMBER_OF_DIFFERENT_PIECE_TYPES; i++)
	{
		retVal = retVal && (first.pieces_of_type[i] == second.pieces_of_type[i]);
	}

	retVal = retVal && (first.king_pos[white] == second.king_pos[white]);
	retVal = retVal && (first.king_pos[black] == second.king_pos[black]);

	return retVal;
}

bool operator!=(const BoardRepresentation& first, const BoardRepresentation& second)
{
    return !(first == second);
}