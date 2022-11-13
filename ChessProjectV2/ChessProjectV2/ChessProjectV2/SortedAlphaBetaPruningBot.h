#pragma once
#include "Medicrius.h"

class SortedAlphaBetaPruningBot : public Medicrius
{
public:
	int get_move(const ChessBoard& board, const MoveList& moves) override;
private:
	bool is_capture_move(const Move& move, const ChessBoard& board) const;

	int get_value_of_move_for_sorting(const Move& givenMove, const ChessBoard& board);

	void parital_insertion_sort(MoveList& list, const ChessBoard& board);

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

