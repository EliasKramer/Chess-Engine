#include "Medicrius.h"

int Medicrius::getMove(const ChessBoard& board, const UniqueMoveList& moves)
{
	return 0;
}

int Medicrius::evaluateBoard(const ChessBoard& board)
{
	BoardRepresentation boardRep = board.getBoardRepresentation();

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

	int score = -1;

	//TODO count material	

	return score;
}

int Medicrius::getMoveRecursively(ChessBoard board, int depth)
{
	return 0;
}
