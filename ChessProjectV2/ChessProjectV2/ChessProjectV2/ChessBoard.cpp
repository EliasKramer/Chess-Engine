#include "ChessBoard.h"

bool ChessBoard::destination_is_same_color(Square start, Direction direction, ChessColor color) const
{
	int newPos = (start + direction);

	if (newPos < A1 || newPos > H8)
	{
		return false;
	}

	return position_is_same_color((Square)newPos, color);
}

bool ChessBoard::position_is_same_color(Square pos, ChessColor color) const
{
	return (_board.pieces_of_color[color] & BB_SQUARE[pos]) != 0;
}

void ChessBoard::add_if_destination_is_valid(MoveList& moves, Square start, Direction dir) const
{
	if (destination_is_on_board(start, dir))
	{
		if (!destination_is_same_color(start, dir, _current_turn_color))
		{
			moves.push_back(Move(start, (Square)(start + dir)));
		}
	}
}

void ChessBoard::add_if_destination_is_color(
	MoveList& moves,
	Square start,
	Direction dir,
	ChessColor color) const
{
	if (destination_is_on_board(start, dir))
	{
		Square newPos = (Square)(start + dir);
		if (position_is_same_color(newPos, color))
		{
			moves.push_back(Move(start, newPos));
		}
	}
}

void ChessBoard::get_pawn_moves(MoveList& moves) const
{
	Direction forward = get_forward_for_color(_current_turn_color);
	BitBoard startRank = _current_turn_color == white ? RANK_2 : RANK_7;

	for (uint8_t currSquareIdx = A1; currSquareIdx <= H8; currSquareIdx++)
	{
		Square currSquare = (Square)currSquareIdx;
		BitBoard piecePosBB = BB_SQUARE[currSquareIdx];

		//if the current square is a pawn and the same color
		if ((piecePosBB &
			_board.pieces_of_type[pawn] &
			_board.pieces_of_color[_current_turn_color]) != 0ULL)
		{
			//one move forward
			if (destination_is_on_board(currSquare, forward))
			{
				Square forwardPos = (Square)(currSquare + forward);
				BitBoard forwardPosBB = BB_SQUARE[forwardPos];

				if ((forwardPosBB & _board.all_pieces) == 0ULL)
				{
					add_pawn_move(moves, currSquare, forwardPos);
					//moves.push_back(Move(currSquare, forwardPos));
					//TODO
					//if move ends on promotion rank it should be a promotion move

					//two moves forward (only possible if one move is possible
					Square doubleForward = (Square)(forwardPos + forward);
					if ((piecePosBB & startRank) != 0 &&
						destination_is_on_board(forwardPos, forward) &&
						(BB_SQUARE[doubleForward] & _board.all_pieces) == 0ULL)
					{
						moves.push_back(Move(currSquare, doubleForward));
					}
				}
			}

			//taking diagonal checks
			//this loop checks one time left and one time right
			Direction leftAndRight[2] = { WEST, EAST };
			for (int i = 0; i < 2; i++)
			{
				Direction direction = (Direction)(leftAndRight[i] + forward);
				ChessColor opponentColor = get_opposite_color(_current_turn_color);

				if (destination_is_same_color(currSquare, direction, opponentColor)
					&& destination_is_on_board(currSquare, direction))
				{
					add_pawn_move(moves, currSquare, (Square)(currSquare + direction));
				}
			}
		}
	}
}

void ChessBoard::get_knight_moves(MoveList& moves) const
{
	for (uint8_t currSquareIdx = A1; currSquareIdx <= H8; currSquareIdx++)
	{
		if ((BB_SQUARE[currSquareIdx] &
			_board.pieces_of_type[knight] &
			_board.pieces_of_color[_current_turn_color]) != 0ULL)
		{
			add_if_destination_is_valid(moves, (Square)currSquareIdx, NORTH_NORTH_EAST);
			add_if_destination_is_valid(moves, (Square)currSquareIdx, EAST_NORTH_EAST);
			add_if_destination_is_valid(moves, (Square)currSquareIdx, EAST_SOUTH_EAST);
			add_if_destination_is_valid(moves, (Square)currSquareIdx, SOUTH_SOUTH_EAST);
			add_if_destination_is_valid(moves, (Square)currSquareIdx, SOUTH_SOUTH_WEST);
			add_if_destination_is_valid(moves, (Square)currSquareIdx, WEST_SOUTH_WEST);
			add_if_destination_is_valid(moves, (Square)currSquareIdx, WEST_NORTH_WEST);
			add_if_destination_is_valid(moves, (Square)currSquareIdx, NORTH_NORTH_WEST);
		}
	}
}

void ChessBoard::get_bishop_moves(MoveList& moves) const
{
	const int numberOfDirections = 4;
	Direction directions[numberOfDirections] =
	{ NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST };

	for (uint8_t currSquareIdx = A1; currSquareIdx <= H8; currSquareIdx++)
	{
		if ((BB_SQUARE[currSquareIdx] &
			_board.pieces_of_type[bishop] &
			_board.pieces_of_color[_current_turn_color]) != 0ULL)
		{
			add_ray_moves(moves, (Square)currSquareIdx, directions, numberOfDirections);
		}
	}

}

void ChessBoard::get_rook_moves(MoveList& moves) const
{
	const int numberOfDirections = 4;
	Direction directions[numberOfDirections] =
	{ NORTH, EAST, SOUTH, WEST };

	for (uint8_t currSquareIdx = A1; currSquareIdx <= H8; currSquareIdx++)
	{
		if ((BB_SQUARE[currSquareIdx] &
			_board.pieces_of_type[rook] &
			_board.pieces_of_color[_current_turn_color]) != 0ULL)
		{
			add_ray_moves(moves, (Square)currSquareIdx, directions, numberOfDirections);
		}
	}
}

void ChessBoard::get_queen_moves(MoveList& moves) const
{
	const int numberOfDirections = 8;
	Direction directions[numberOfDirections] =
	{ NORTH, EAST, SOUTH, WEST, NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST };

	for (uint8_t currSquareIdx = A1; currSquareIdx <= H8; currSquareIdx++)
	{
		if ((BB_SQUARE[currSquareIdx] &
			_board.pieces_of_type[queen] &
			_board.pieces_of_color[_current_turn_color]) != 0ULL)
		{
			add_ray_moves(moves, (Square)currSquareIdx, directions, numberOfDirections);
		}
	}
}

void ChessBoard::get_king_moves(MoveList& moves) const
{
	for (uint8_t currSquareIdx = A1; currSquareIdx <= H8; currSquareIdx++)
	{
		if ((BB_SQUARE[currSquareIdx] &
			_board.pieces_of_type[king] &
			_board.pieces_of_color[_current_turn_color]) != 0ULL)
		{
			add_if_destination_is_valid(moves, (Square)currSquareIdx, NORTH);
			add_if_destination_is_valid(moves, (Square)currSquareIdx, NORTH_EAST);
			add_if_destination_is_valid(moves, (Square)currSquareIdx, EAST);
			add_if_destination_is_valid(moves, (Square)currSquareIdx, SOUTH_EAST);
			add_if_destination_is_valid(moves, (Square)currSquareIdx, SOUTH);
			add_if_destination_is_valid(moves, (Square)currSquareIdx, SOUTH_WEST);
			add_if_destination_is_valid(moves, (Square)currSquareIdx, WEST);
			add_if_destination_is_valid(moves, (Square)currSquareIdx, NORTH_WEST);
		}
	}
}

void ChessBoard::add_pawn_move(MoveList& moves, Square start, Square dest) const
{
	BitBoard promotionRank = _current_turn_color == white ? RANK_8 : RANK_1;

	if ((BB_SQUARE[dest] & promotionRank) != 0ULL)
	{
		moves.push_back(Move(start, dest, _current_turn_color, MoveFlag::promote_queen));
		moves.push_back(Move(start, dest, _current_turn_color, MoveFlag::promote_rook));
		moves.push_back(Move(start, dest, _current_turn_color, MoveFlag::promote_bishop));
		moves.push_back(Move(start, dest, _current_turn_color, MoveFlag::promote_knight));
	}
	else
	{
		moves.push_back(Move(start, dest));
	}
}

void ChessBoard::get_castling_moves(MoveList& moves) const
{
	//can improve performance -> 
	//combine all fields in a bitboard and check for the non-sliding pieces
	//if the can take at these positions
	for (int castlingIdx = 0; castlingIdx < 2; castlingIdx++)
	{
		CastlingType currCastlingType = (CastlingType)castlingIdx;

		if (_can_castle[_current_turn_color][currCastlingType])
		{
			bool castlingAllowed = true;
			for (int i = 0; i < 3; i++)
			{
				Square currSquareToCheck =
					SQUARES_FOR_KING_CASTLING[_current_turn_color][currCastlingType][i];

				//square should not be attacked or should not have any piece there
				if (field_is_under_attack(currSquareToCheck) ||
					(i != 0 && (_board.all_pieces & BB_SQUARE[currSquareToCheck]) != 0ULL))
				{
					castlingAllowed = false;
				}
			}
			//can be done better, but has to do for now
			if (currCastlingType == castle_long)
			{
				//square that can be in check, but has to have no piece on it
				Square passingSquare = _current_turn_color == white ? B1 : B8;
				if ((_board.all_pieces & BB_SQUARE[passingSquare]) != 0ULL)
				{
					castlingAllowed = false;
				}
			}

			if (castlingAllowed)
			{
				moves.push_back(Move(_current_turn_color, currCastlingType));
			}
		}
	}
}

void ChessBoard::get_en_passant_move(MoveList& moves) const
{
	if (_en_passant_square == SQUARE_NONE)
	{
		return;
	}

	Direction backwards = get_backward_for_color(_current_turn_color);

	Direction directionsWhereOwnPawnCouldBe[2] =
	{ (Direction)(backwards + EAST), (Direction)(backwards + WEST) };

	for (int i = 0; i < 2; i++)
	{
		if (destination_is_on_board(_en_passant_square, directionsWhereOwnPawnCouldBe[i]))
		{
			Square ownPawnPos = (Square)(_en_passant_square + directionsWhereOwnPawnCouldBe[i]);
			if ((BB_SQUARE[ownPawnPos] &
				_board.pieces_of_color[_current_turn_color] &
				_board.pieces_of_type[pawn]) != 0ULL)
			{
				Square pawnPosToDelete = (Square)(_en_passant_square + backwards);
				moves.push_back(Move(ownPawnPos, _en_passant_square));
			}
		}
	}
}

void ChessBoard::add_ray_moves(
	MoveList& moves,
	Square start,
	Direction directions[],
	int numberOfDirections) const
{
	ChessColor opponentColor = get_opposite_color(_current_turn_color);

	for (int i = 0; i < numberOfDirections; i++)
	{
		Direction currentDirection = directions[i];

		Square currentSquare = start;
		while (true)
		{
			//if the new position is on the board
			if (destination_is_on_board(currentSquare, currentDirection))
			{
				//set the new position
				currentSquare = (Square)(currentSquare + currentDirection);

				//if the new position is the same color as the piece to check
				if (position_is_same_color(currentSquare, _current_turn_color))
				{
					//you cannot go on a square where a piece of the same color is
					break;
				}
				else if (position_is_same_color(currentSquare, opponentColor))
				{
					//if an opponent is on the new field you can take him,
					//but cannot continue after that (you cannot jump over opponents)
					moves.push_back(Move(start, currentSquare));
					break;
				}
				else {
					//if there is no piece at the new position you can move there.
					moves.push_back(Move(start, currentSquare));
				}
			}
			else {
				//if the new position is not on the board, the search should not continue
				break;
			}
		}
	}
}

bool ChessBoard::field_is_under_attack(Square pos, BitBoard moveBB) const
{
	//is only used for king checks and castling, so no en passant implemented

	ChessColor opponentColor = get_opposite_color(_current_turn_color);

	BitBoard newCurrentColorBB = _board.pieces_of_color[_current_turn_color] ^ moveBB;

	BitBoard opponentColorBB = (_board.pieces_of_color[opponentColor] & (~moveBB));

	BitBoard knightBB = _board.pieces_of_type[knight];
	BitBoard pawnsBB = _board.pieces_of_type[pawn];
	BitBoard kingsBB = _board.pieces_of_type[king];

	//gets attacked by knight
	if ((KNIGHT_ATTACK_BB[pos] &
		opponentColorBB &
		knightBB) != 0ULL)
	{
		return true;
	}

	//gets attacked by pawn
	//it is handled like the current field is a pawn, 
	//because if the current field has a pawn on its attacking squares, 
	//it can also be attacked by the opponent pawn
	if ((PAWN_ATTACK_BB[_current_turn_color][pos] &
		opponentColorBB &
		pawnsBB) != 0ULL)
	{
		return true;
	}

	//field gets attacked by king
	if ((KING_ATTACKS_BB[pos] &
		opponentColorBB &
		kingsBB) != 0ULL)
	{
		return true;
	}

	//raycast in every direction and check for queen, rook or bishop attacks
	return field_gets_attacked_by_sliding_piece(pos, moveBB);
}

bool ChessBoard::field_gets_attacked_by_sliding_piece(Square pos, BitBoard moveBB) const
{
	ChessColor opponentColor = get_opposite_color(_current_turn_color);

	BitBoard queenBB = _board.pieces_of_type[queen];
	BitBoard rookBB = _board.pieces_of_type[rook];
	BitBoard bishopBB = _board.pieces_of_type[bishop];

	BitBoard newCurrentColorBB = _board.pieces_of_color[_current_turn_color] ^ moveBB;

	BitBoard moveBBWithoutStart = moveBB & ~_board.pieces_of_color[_current_turn_color];

	//if there are 2 destination fields, it is an en passant move
	if (((moveBBWithoutStart & _board.pieces_of_color[opponentColor]) != 0ULL) &&
		((moveBBWithoutStart & ~_board.pieces_of_color[opponentColor]) != 0ULL))
	{
		newCurrentColorBB &= ~_board.pieces_of_color[opponentColor];
	}

	BitBoard opponentColorBB = (_board.pieces_of_color[opponentColor] & (~moveBB));

	for (int i = 0; i < 8; i++)
	{
		Direction currentDirection = ALL_SLIDING_DIRECTIONS[i];

		Square currentSquare = pos;
		while (true)
		{
			//if the new position would be on the board
			if (destination_is_on_board(currentSquare, currentDirection))
			{
				//set the new position
				currentSquare = (Square)(currentSquare + currentDirection);

				//if the new position is the same color as the piece to check
				if (square_overlaps_with_BB(currentSquare, newCurrentColorBB))
				{
					//you cannot go on a square where a piece of the same color is
					break;
				}
				else if (square_overlaps_with_BB(currentSquare, opponentColorBB))
				{
					BitBoard currPosBB = BB_SQUARE[currentSquare];

					bool currDirIsDiagonal = i > 3;

					//found piece is a queen -> will attack no matter in which direction you are sliding
					if ((currPosBB & queenBB) != 0ULL)
					{
						//is queen
						return true;
					}
					//if found piece is a rook or a bishop, sliding direction matters
					else if (currDirIsDiagonal)
					{
						if ((currPosBB & bishopBB) != 0ULL)
						{
							//is bishop
							return true;
						}
					}
					else
					{
						if ((currPosBB & rookBB) != 0ULL)
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

bool ChessBoard::move_is_legal(const Move move) const
{
	//if move is castle -> return true
	if (move.getFlag() == castle)
	{
		//because a castling move has been checked to be legal before
		return true;
	}

	Square start = move.getStart();
	Square dest = move.getDestination();

	//TODO
	return true;
	/*BitBoard BBforNextMove = move.getBBWithMoveDone();

	Square kingPos = _board.king_pos[_current_turn_color];

	return start == kingPos ?
		!field_is_under_attack(dest, BBforNextMove) :
		!field_is_under_attack(kingPos, BBforNextMove);*/
}

bool ChessBoard::is_capture_move(const Move move) const
{
	MoveFlag flag = move.getFlag();
	if (flag == castle)
	{
		return false;
	}
	else if(flag == en_passant)
	{
		return true;
	}

	BitBoard oppositeColorBB = _board.pieces_of_color[get_opposite_color(_current_turn_color)];
	BitBoard potentialCaptureField = BB_SQUARE[move.getDestination()];

	return bitboards_overlap(oppositeColorBB, potentialCaptureField);
}

void ChessBoard::update_castling_rights_after_move(const Move& m)
{
	BitBoard start = BB_SQUARE[m.getStart()];
	BitBoard dest = BB_SQUARE[m.getDestination()];
	if (bitboards_overlap(start, SQUARES_EFFECTED_BY_CASTLING_BB) ||
		bitboards_overlap(dest, SQUARES_EFFECTED_BY_CASTLING_BB))
	{

		if ((KINGFILE & BACKRANK[_current_turn_color] & start) != 0)
		{
			_can_castle[_current_turn_color][castle_long] = false;
			_can_castle[_current_turn_color][castle_short] = false;
		}

		for (int i = 0; i < 2; i++)
		{
			ChessColor currCol = (ChessColor)i;
			for (int j = 0; j < 2; j++)
			{
				CastlingType currCastleType = (CastlingType)j;
				BitBoard fieldToCheck = BACKRANK[currCol] & CASTLINGSIDE[currCastleType];
				if (bitboards_overlap(start, fieldToCheck) ||
					bitboards_overlap(dest, fieldToCheck))
				{
					_can_castle[currCol][currCastleType] = false;
				}
			}
		}
	}
}

void ChessBoard::update_en_passant_rights_after_move(const Move& m)
{
	_en_passant_square = SQUARE_NONE;
	Square start = m.getStart();
	if (square_overlaps_with_BB(start, _board.pieces_of_type[pawn]))
	{
		Square dest = m.getDestination();
		BitBoard startRankForDoubleMove = _current_turn_color == white ? RANK_2 : RANK_7;
		BitBoard destRankForDoubleMove = _current_turn_color == white ? RANK_4 : RANK_5;

		if (square_overlaps_with_BB(start, startRankForDoubleMove) &&
			square_overlaps_with_BB(dest, destRankForDoubleMove))
		{
			_en_passant_square = (Square)(start + get_forward_for_color(_current_turn_color));
		}
	}
}

void ChessBoard::update_50_move_rule(const Move& m)
{
	BitBoard startBB = BB_SQUARE[m.getStart()];
	BitBoard destBB = BB_SQUARE[m.getDestination()];
	ChessColor opponentColor = get_opposite_color(_current_turn_color);

	if (bitboards_overlap(startBB, _board.pieces_of_type[pawn]) ||
		bitboards_overlap(destBB, _board.pieces_of_color[opponentColor]))
	{
		_half_move_clock = 0;
	}
	else
	{
		_half_move_clock++;
	}
}

bool ChessBoard::insufficient_material_check() const
{
	//if any of these pieces are on the board, the game can be won
	if (_board.pieces_of_type[queen] != 0 ||
		_board.pieces_of_type[rook] != 0 ||
		_board.pieces_of_type[pawn] != 0)
	{
		return false;
	}

	if (_board.pieces_of_type[bishop] == 0 &&
		_board.pieces_of_type[knight] == 0)
	{
		return true;
	}

	//TODO
	//if only one bishop or one knight is on the board, the game cant be won

	return false;
}

char ChessBoard::get_piece_at(Square pos) const
{
	BitBoard posBB = BB_SQUARE[pos];

	if (bitboards_overlap(posBB, ~_board.all_pieces))
	{
		return ' ';
	}

	char pieceChar = '~';

	for (int i = 0; i < NUMBER_OF_DIFFERENT_PIECE_TYPES; i++)
	{
		PieceType currType = (PieceType)i;

		if (bitboards_overlap(_board.pieces_of_type[currType], posBB))
		{
			pieceChar = PIECETYPE_CHAR[currType];
		}
	}

	if (pieceChar == '~')
	{
		throw "Could not find PieceType in the Chessboard configuration";
	}

	if (bitboards_overlap(_board.pieces_of_color[black], posBB))
	{
		pieceChar = char_to_lower(pieceChar);
	}

	return pieceChar;
}


ChessBoard::ChessBoard(std::string given_fen_code)
{
	//set all castling rights to false at the beginning
	for (int i = 0; i < 2; i++)
	{
		ChessColor currColor = (ChessColor)i;
		for (int j = 0; j < 2; j++)
		{
			CastlingType currCastleType = (CastlingType)j;
			_can_castle[currColor][currCastleType] = false;
		}
	}

	std::string prefixForErrors = "ERROR The given FEN Code is invalid. ";

	std::vector<std::string> split_fen_code = split_string(given_fen_code, ' ');
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
		else
		{
			ChessPiece piece(currChar);

			_board.set_at_position(piece, (Square)boardPos);

			currFile++;
		}
	}

	//get the turn color
	if (split_fen_code[1].size() != 1)
	{
		throw prefixForErrors + "The turn color should only occupy 1 char";
	}
	_current_turn_color =
		split_fen_code[1][0] == 'w' ? white :
		split_fen_code[1][0] == 'b' ? black :
		throw prefixForErrors + "The color could not be found";

	//castling rights
	for (int i = 0; i < split_fen_code[2].size(); i++)
	{
		char currChar = split_fen_code[2][i];

		if (currChar != '-')
		{
			_can_castle
				[get_color_of_fen_char(currChar)]
			[get_castling_type_of_fen_char(currChar)] = true;
		}
	}

	//en passant field
	_en_passant_square = get_square_from_string(split_fen_code[3]);

	//50 move rule - after half moves without pushing a pawn and
	//without capturing a piece the game ends in a draw
	_half_move_clock = std::stoi(split_fen_code[4]);

	//keeps track of the moves (one move consists of one move of white and one move of black)
	_move_number = std::stoi(split_fen_code[5]);
}

std::string ChessBoard::get_string()
{
	std::string result = "";
	std::string rowSeperatorString = "\n+---+---+---+---+---+---+---+---+\n";
	result += rowSeperatorString;

	for (int rank = 7; rank >= 0; rank--)
	{
		for (int file = 0; file < 8; file++)
		{
			Square pos = (Square)(rank * 8 + file);
			result += "| ";
			result += get_piece_at(pos);
			result += " ";

		}
		result += "|" + std::to_string(rank + 1);
		result += rowSeperatorString;
	}
	result += "  a   b   c   d   e   f   g   h\n";

	return result;
}

std::string ChessBoard::get_fen()
{
	std::string result = "";

	//written with copilot. can be improved i think

	for (int rank = 7; rank >= 0; rank--)
	{
		int emptyFields = 0;
		for (int file = 0; file < 8; file++)
		{
			Square pos = (Square)(rank * 8 + file);
			char pieceChar = get_piece_at(pos);

			if (pieceChar == ' ')
			{
				emptyFields++;
			}
			else
			{
				if (emptyFields > 0)
				{
					result += std::to_string(emptyFields);
					emptyFields = 0;
				}
				result += pieceChar;
			}
		}
		if (emptyFields > 0)
		{
			result += std::to_string(emptyFields);
		}
		if (rank > 0)
		{
			result += "/";
		}
	}

	result += " ";

	result += _current_turn_color == white ? "w" : "b";

	result += " ";

	if (_can_castle[white][castle_short] ||
		_can_castle[white][castle_long] ||
		_can_castle[black][castle_short] ||
		_can_castle[black][castle_long])
	{
		if (_can_castle[white][castle_short])
		{
			result += "K";
		}
		if (_can_castle[white][castle_long])
		{
			result += "Q";
		}
		if (_can_castle[black][castle_short])
		{
			result += "k";
		}
		if (_can_castle[black][castle_long])
		{
			result += "q";
		}
	}
	else
	{
		result += "-";
	}

	result += " ";

	result += SQUARE_STRING[_en_passant_square];

	result += " ";

	result += std::to_string(_half_move_clock);

	result += " ";

	result += std::to_string(_move_number);

	return result;
}

ChessColor ChessBoard::get_current_turn_color() const
{
	return _current_turn_color;
}

int ChessBoard::get_number_of_moves_played() const
{
	return _move_number;
}

bool ChessBoard::is_king_in_check() const
{
	return field_is_under_attack(_board.king_pos[_current_turn_color]);
}

MoveList ChessBoard::get_all_legal_moves() const
{
	MoveList moveList;

	BitBoard squaresUnderAttack = BITBOARD_NONE;
	
	//get all squares that are under attack
	Square kingPos = _board.king_pos[_current_turn_color];
	
	
	

	get_pawn_moves(moveList);
	get_knight_moves(moveList);
	get_bishop_moves(moveList);
	get_rook_moves(moveList);
	get_queen_moves(moveList);
	get_king_moves(moveList);

	get_castling_moves(moveList);
	get_en_passant_move(moveList);

	return moveList;
}

MoveList ChessBoard::get_all_legal_capture_moves() const
{
	MoveList list = get_all_legal_moves();

	list.erase
	(
		std::remove_if
		(
			list.begin(),
			list.end(),
			[this](const Move move)
			{
				return !is_capture_move(move);
			}
		),
		list.end()
				);

	return list;
}

void ChessBoard::make_move(const Move& move)
{
	Square moveStart = move.getStart();
	Square moveDest = move.getDestination();

	update_castling_rights_after_move(move);
	update_en_passant_rights_after_move(move);
	update_50_move_rule(move);

	move.execute(_board);

	if (moveStart == _board.king_pos[_current_turn_color])
	{
		_board.king_pos[_current_turn_color] = moveDest;
	}

	if (_current_turn_color == black)
	{
		_move_number++;
	}

	_current_turn_color = get_opposite_color(_current_turn_color);
}

ChessBoard ChessBoard::get_copy_by_value() const
{
	ChessBoard board(EMPTY_FEN);
	board._board = _board;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			board._can_castle[i][j] = _can_castle[i][j];
		}
	}

	board._current_turn_color = _current_turn_color;

	board._en_passant_square = _en_passant_square;

	board._half_move_clock = _half_move_clock;

	board._move_number = _move_number;

	return board;
}

GameState ChessBoard::get_game_state() const
{
	if (get_all_legal_moves().size() == 0)
	{
		if (field_is_under_attack(_board.king_pos[_current_turn_color]))
		{
			return _current_turn_color == white ? black_won : white_won;
		}
		else
		{
			return stalemate;
		}
	}
	if (_half_move_clock == 50 ||
		insufficient_material_check())
	{
		return draw;
	}
	return ongoing;
}

GameDurationState ChessBoard::get_game_duration_state() const
{
	//HAS TO BE IMPROVED ALOT
	// 
	// 
	//description at the end of: https://www.chessprogramming.org/Simplified_Evaluation_Function

	//definiton on the site of when the endgame begins:
	//- Both sides have no queens or
	//- Every side which has a queen has additionally no other pieces or one minorpiece maximum.

	//there are different game states for different colors
	//for example: if one color got lots of pieces, but the other almost none, 
	//it is useful to bring the king into the game
	ChessColor col = _current_turn_color;
	BitBoard colorBB = _board.pieces_of_color[col];

	if (((_board.pieces_of_type[queen] == 0ULL) &&
		//a queen can be exchanged very early on. So we need to check if the game has already progressed a bit
		_move_number > 10))
	{
		//gets activated often at the start of games, 
		//which is not exactly an "endgame" state
		//return EndGame;
	}


	if ((_board.pieces_of_type[queen] & colorBB) != 0ULL)
	{
		BitBoard colorBBWithoutKingOrQueen =
			colorBB &
			~_board.pieces_of_type[king] &
			~_board.pieces_of_type[queen];

		if ((colorBBWithoutKingOrQueen & ~_board.pieces_of_type[bishop]) == 0ULL ||
			(colorBBWithoutKingOrQueen & ~_board.pieces_of_type[knight]) == 0ULL ||
			(colorBBWithoutKingOrQueen & ~_board.pieces_of_type[pawn]) == 0ULL ||
			(colorBBWithoutKingOrQueen & ~_board.pieces_of_type[rook]) == 0ULL)
		{
			return EndGame;
		}
	}


	return MidGame;
}

BoardRepresentation ChessBoard::get_board_representation() const
{
	return _board;
}

bool operator==(const ChessBoard& first, const ChessBoard& second)
{
	bool retVal = first._board == second._board;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			retVal = retVal && (first._can_castle[i][j] == second._can_castle[i][j]);
		}
	}

	retVal = retVal && (first._current_turn_color == second._current_turn_color);

	retVal = retVal && (first._en_passant_square == second._en_passant_square);

	retVal = retVal && (first._half_move_clock == second._half_move_clock);

	retVal = retVal && (first._move_number == second._move_number);

	return retVal;
}

bool operator!=(const ChessBoard& first, const ChessBoard& second)
{
	return !(first == second);
}
