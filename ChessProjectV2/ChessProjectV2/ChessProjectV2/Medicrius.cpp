#include "Medicrius.h"

int Medicrius::getMove(const ChessBoard& board, const UniqueMoveList& moves)
{
	return 0;
}

int Medicrius::evaluateBoard(const ChessBoard& board)
{
	//regulates how much the material (the pieces on the board) is worth
	const int materialWeight = 100;
	const int positionWeight = 50;
	
	BoardRepresentation boardRep = board.getBoardRepresentation();

	//get the obvious out the way 
	// - if white wins return highest possible number
	// - if black wins return lowest possible number
	GameState gameState = board.getGameState();
	switch (gameState)
	{
	case WhiteWon:
		return INT_MAX;
	case BlackWon:
		return INT_MIN;
	case Stalemate:
		return 0;
	case Draw:
		return 0;
	}

	//now calculate the score
	int score = 0;

	for (int i = A1; i <= H8; i++)
	{
		BitBoard idxBB = BB_SQUARE[i];

		//iterate over every type except king
		for (int typeIdx = 0; typeIdx <= Queen; typeIdx++)
		{
			//if current square overlaps with the current piece type
			if (bitboardsOverlap(idxBB, boardRep._piecesOfType[typeIdx]))
			{
				//get the material value of the piece type
				int materialValue = PIECETYPE_VALUE[typeIdx];
				//if pieces are black, negate the value
				if (bitboardsOverlap(idxBB, boardRep._piecesOfColor[Black]))
				{
					materialValue *= -1;
				}
				//add the value to the total score multiplied by material weight
				score += (materialValue * materialWeight);
			}
		}
	}

	return score;
}

int Medicrius::getMoveRecursively(ChessBoard board, int depth)
{
	return 0;
}
