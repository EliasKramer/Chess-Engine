#pragma once
#include "Medicrius.h"

class SortedAlphaBetaPruningBot : public Medicrius
{
public:
	int getMove(const ChessBoard& board, const UniqueMoveList& moves) override;
private:
	int getValueOfMoveForSorting(const Move& givenMove, const ChessBoard& board);

	bool compareMoves(const Move m1, const Move m2);

	int getMoveScoreRecursively(
		ChessBoard board,
		int depth,
		bool isMaximizingPlayer,
		int alpha,
		int beta,
		int& nodesSearched,
		int& endStatesSearched,
		int& prunedBranches
	);
};

