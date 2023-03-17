#pragma once
#include "Medicrius.h"

class UnoptimizedMinimaxBot : public Medicrius
{
public:
	int getMove(const ChessBoard& board, const UniqueMoveList& moves) override;
private:
	int minimax(
		ChessBoard board,
		int depth,
		int& nodesSearched,
		int& endStatesSearched);
};