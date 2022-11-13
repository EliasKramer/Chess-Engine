#pragma once
#include "Medicrius.h"

class AlphaBetaPruningBot : public Medicrius
{
public:
	int get_move(const ChessBoard& board, const MoveList& moves) override;
private:
	int get_move_score_recursively(
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