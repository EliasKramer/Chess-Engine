#pragma once
#include "Medicrius.h"

class SortedAlphaBetaPruningBot : public Medicrius
{
public:
	int getMove(const ChessBoard& board, const UniqueMoveList& moves) override;
private:
	bool isCaptureMove(const Move& move, const ChessBoard& board) const;

	int getValueOfMoveForSorting(const Move& givenMove, const ChessBoard& board);

	void partialInsertionSort(UniqueMoveList& list, const ChessBoard& board);

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

