#pragma once
#include "Medicrius.h"

class UnoptimizedMinimaxBot : public Medicrius
{
public:
	int get_move(const ChessBoard& board, const MoveList& moves) override;
private:
	int minimax(
		ChessBoard board,
		int depth,
		int& nodesSearched,
		int& endStatesSearched);
};